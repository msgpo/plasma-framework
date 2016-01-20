/*
 *   Copyright 2012 Marco Martin <mart@kde.org>
 *   Copyright 2014 David Edmundson <davidedmudnson@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ICONITEM_H
#define ICONITEM_H

#include <QIcon>
#include <QQuickItem>
#include <QPixmap>
#include <QVariant>
#include <QTimer>

#include <plasma/svg.h>

class QPropertyAnimation;

/**
 * @class IconItem
 * @short Displays an icon, either from the standard QIcon system or where applicable from the theme SVG files
 */
class IconItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QVariant source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(Plasma::Theme::ColorGroup colorGroup READ colorGroup WRITE setColorGroup NOTIFY colorGroupChanged)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth NOTIFY smoothChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated NOTIFY animatedChanged)
    Q_PROPERTY(bool usesPlasmaTheme READ usesPlasmaTheme WRITE setUsesPlasmaTheme NOTIFY usesPlasmaThemeChanged)
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged)
    Q_PROPERTY(int paintedWidth READ paintedWidth NOTIFY paintedSizeChanged)
    Q_PROPERTY(int paintedHeight READ paintedHeight NOTIFY paintedSizeChanged)

public:

    IconItem(QQuickItem *parent = 0);
    ~IconItem();

    void setSource(const QVariant &source);
    QVariant source() const;

    void setColorGroup(Plasma::Theme::ColorGroup group);
    Plasma::Theme::ColorGroup colorGroup() const;

    bool isActive() const;
    void setActive(bool active);

    void setSmooth(const bool smooth);
    bool smooth() const;

    bool isAnimated() const;
    void setAnimated(bool animated);

    bool usesPlasmaTheme() const;
    void setUsesPlasmaTheme(bool usesPlasmaTheme);

    bool isValid() const;

    int paintedWidth() const;
    int paintedHeight() const;

    void updatePolish() Q_DECL_OVERRIDE;
    QSGNode* updatePaintNode(QSGNode * oldNode, UpdatePaintNodeData * updatePaintNodeData) Q_DECL_OVERRIDE;

    void geometryChanged(const QRectF &newGeometry,
                         const QRectF &oldGeometry) Q_DECL_OVERRIDE;

    void componentComplete() Q_DECL_OVERRIDE;

Q_SIGNALS:
    void activeChanged();
    void sourceChanged();
    void smoothChanged();
    void animatedChanged();
    void usesPlasmaThemeChanged();
    void validChanged();
    void colorGroupChanged();
    void paintedSizeChanged();

private Q_SLOTS:
    void schedulePixmapUpdate();
    void animationFinished();
    void valueChanged(const QVariant &value);

private:
    void loadPixmap();

    //all the ways we can set an source. Only one of them will be valid
    QIcon m_icon;
    Plasma::Svg *m_svgIcon;
    QPixmap m_pixmapIcon;
    QImage m_imageIcon;
    //this contains the raw variant it was passed
    QVariant m_source;

    QSizeF m_implicitSize;

    bool m_smooth;
    bool m_active;
    bool m_animated;
    bool m_usesPlasmaTheme;

    bool m_textureChanged;
    bool m_sizeChanged;

    bool m_svgFromIconLoader;

    QPixmap m_iconPixmap;
    QPixmap m_oldIconPixmap;

    Plasma::Theme::ColorGroup m_colorGroup;

    //animation on pixmap change
    QPropertyAnimation *m_animation;
    qreal m_animValue;

};

#endif
