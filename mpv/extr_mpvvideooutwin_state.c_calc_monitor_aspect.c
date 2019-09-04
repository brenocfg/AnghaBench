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
struct mp_vo_opts {double monitor_pixel_aspect; int force_monitor_aspect; } ;

/* Variables and functions */

__attribute__((used)) static void calc_monitor_aspect(struct mp_vo_opts *opts, int scr_w, int scr_h,
                                double *pixelaspect, int *w, int *h)
{
    *pixelaspect = 1.0 / opts->monitor_pixel_aspect;

    if (scr_w > 0 && scr_h > 0 && opts->force_monitor_aspect)
        *pixelaspect = 1.0 / (opts->force_monitor_aspect * scr_h / scr_w);

    if (*pixelaspect < 1) {
        *h /= *pixelaspect;
    } else {
        *w *= *pixelaspect;
    }
}