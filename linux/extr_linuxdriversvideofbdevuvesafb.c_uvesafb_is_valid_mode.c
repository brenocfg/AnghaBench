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
struct fb_videomode {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_2__ {scalar_t__ gtf; } ;
struct fb_info {int /*<<< orphan*/  par; int /*<<< orphan*/  var; TYPE_1__ monspecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVESAFB_EXACT_RES ; 
 scalar_t__ fb_validate_mode (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  fb_videomode_to_var (int /*<<< orphan*/ *,struct fb_videomode*) ; 
 int uvesafb_vbe_find_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvesafb_is_valid_mode(struct fb_videomode *mode,
				 struct fb_info *info)
{
	if (info->monspecs.gtf) {
		fb_videomode_to_var(&info->var, mode);
		if (fb_validate_mode(&info->var, info))
			return 0;
	}

	if (uvesafb_vbe_find_mode(info->par, mode->xres, mode->yres, 8,
				UVESAFB_EXACT_RES) == -1)
		return 0;

	return 1;
}