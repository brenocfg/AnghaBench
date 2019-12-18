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
struct sub_bitmaps {int num_parts; struct sub_bitmap* parts; } ;
struct sub_bitmap {int x; int y; int dw; double w; int dh; double h; } ;
struct mp_osd_res {int w; int ml; int mr; int h; int mt; int mb; double display_par; } ;

/* Variables and functions */

void osd_rescale_bitmaps(struct sub_bitmaps *imgs, int frame_w, int frame_h,
                         struct mp_osd_res res, double compensate_par)
{
    int vidw = res.w - res.ml - res.mr;
    int vidh = res.h - res.mt - res.mb;
    double xscale = (double)vidw / frame_w;
    double yscale = (double)vidh / frame_h;
    if (compensate_par < 0)
        compensate_par = xscale / yscale / res.display_par;
    if (compensate_par > 0)
        xscale /= compensate_par;
    int cx = vidw / 2 - (int)(frame_w * xscale) / 2;
    int cy = vidh / 2 - (int)(frame_h * yscale) / 2;
    for (int i = 0; i < imgs->num_parts; i++) {
        struct sub_bitmap *bi = &imgs->parts[i];
        bi->x = (int)(bi->x * xscale) + cx + res.ml;
        bi->y = (int)(bi->y * yscale) + cy + res.mt;
        bi->dw = (int)(bi->w * xscale + 0.5);
        bi->dh = (int)(bi->h * yscale + 0.5);
    }
}