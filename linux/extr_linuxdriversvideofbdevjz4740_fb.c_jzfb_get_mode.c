#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct jzfb {TYPE_1__* pdata; } ;
struct fb_videomode {scalar_t__ xres; scalar_t__ yres; } ;
struct fb_var_screeninfo {scalar_t__ xres; scalar_t__ yres; } ;
struct TYPE_2__ {size_t num_modes; struct fb_videomode* modes; } ;

/* Variables and functions */

__attribute__((used)) static struct fb_videomode *jzfb_get_mode(struct jzfb *jzfb,
	struct fb_var_screeninfo *var)
{
	size_t i;
	struct fb_videomode *mode = jzfb->pdata->modes;

	for (i = 0; i < jzfb->pdata->num_modes; ++i, ++mode) {
		if (mode->xres == var->xres && mode->yres == var->yres)
			return mode;
	}

	return NULL;
}