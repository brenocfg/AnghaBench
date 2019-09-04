#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int hdisplay; unsigned int vdisplay; } ;
typedef  TYPE_1__ drmModeModeInfo ;

/* Variables and functions */
 scalar_t__ isnan (double) ; 
 double mode_get_Hz (TYPE_1__ const*) ; 
 scalar_t__ round (double const) ; 

__attribute__((used)) static bool mode_match(const drmModeModeInfo *mode,
                       unsigned int width,
                       unsigned int height,
                       double refresh)
{
    if (isnan(refresh)) {
        return
            (mode->hdisplay == width) &&
            (mode->vdisplay == height);
    } else {
        const double mode_refresh = mode_get_Hz(mode);
        return
            (mode->hdisplay == width) &&
            (mode->vdisplay == height) &&
            ((int)round(refresh*100) == (int)round(mode_refresh*100));
    }
}