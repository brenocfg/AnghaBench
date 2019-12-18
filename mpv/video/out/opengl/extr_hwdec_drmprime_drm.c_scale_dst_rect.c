#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ra_hwdec {struct priv* priv; } ;
struct priv {double display_w; double display_h; } ;
struct mp_rect {double x0; double x1; double y0; double y1; } ;

/* Variables and functions */

__attribute__((used)) static void scale_dst_rect(struct ra_hwdec *hw, int source_w, int source_h ,struct mp_rect *src, struct mp_rect *dst)
{
    struct priv *p = hw->priv;

    // drm can allow to have a layer that has a different size from framebuffer
    // we scale here the destination size to video mode
    double hratio = p->display_w / (double)source_w;
    double vratio = p->display_h / (double)source_h;
    double ratio = hratio <= vratio ? hratio : vratio;

    dst->x0 = src->x0 * ratio;
    dst->x1 = src->x1 * ratio;
    dst->y0 = src->y0 * ratio;
    dst->y1 = src->y1 * ratio;

    int offset_x = (p->display_w - ratio * source_w) / 2;
    int offset_y = (p->display_h - ratio * source_h) / 2;

    dst->x0 += offset_x;
    dst->x1 += offset_x;
    dst->y0 += offset_y;
    dst->y1 += offset_y;
}