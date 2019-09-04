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
struct m_geometry {double w; double h; int x; int y; scalar_t__ y_sign; scalar_t__ y_per; scalar_t__ x_sign; scalar_t__ x_per; scalar_t__ xy_valid; scalar_t__ h_per; scalar_t__ w_per; scalar_t__ wh_valid; } ;

/* Variables and functions */
 int INT_MIN ; 

void m_geometry_apply(int *xpos, int *ypos, int *widw, int *widh,
                      int scrw, int scrh, struct m_geometry *gm)
{
    if (gm->wh_valid) {
        int prew = *widw, preh = *widh;
        if (gm->w > 0)
            *widw = gm->w_per ? scrw * (gm->w / 100.0) : gm->w;
        if (gm->h > 0)
            *widh = gm->h_per ? scrh * (gm->h / 100.0) : gm->h;
        // keep aspect if the other value is not set
        double asp = (double)prew / preh;
        if (gm->w > 0 && !(gm->h > 0)) {
            *widh = *widw / asp;
        } else if (!(gm->w > 0) && gm->h > 0) {
            *widw = *widh * asp;
        }
        // Center window after resize. If valid x:y values are passed to
        // geometry, then those values will be overriden.
        *xpos += prew / 2 - *widw / 2;
        *ypos += preh / 2 - *widh / 2;
    }

    if (gm->xy_valid) {
        if (gm->x != INT_MIN) {
            *xpos = gm->x;
            if (gm->x_per)
                *xpos = (scrw - *widw) * (*xpos / 100.0);
            if (gm->x_sign)
                *xpos = scrw - *widw - *xpos;
        }
        if (gm->y != INT_MIN) {
            *ypos = gm->y;
            if (gm->y_per)
                *ypos = (scrh - *widh) * (*ypos / 100.0);
            if (gm->y_sign)
                *ypos = scrh - *widh - *ypos;
        }
    }
}