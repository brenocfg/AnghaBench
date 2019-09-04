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
struct sh_mobile_lcdc_overlay {int enabled; } ;
struct fb_info {struct sh_mobile_lcdc_overlay* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  sh_mobile_lcdc_overlay_setup (struct sh_mobile_lcdc_overlay*) ; 

__attribute__((used)) static int sh_mobile_lcdc_overlay_blank(int blank, struct fb_info *info)
{
	struct sh_mobile_lcdc_overlay *ovl = info->par;

	ovl->enabled = !blank;
	sh_mobile_lcdc_overlay_setup(ovl);

	/* Prevent the backlight from receiving a blanking event by returning
	 * a non-zero value.
	 */
	return 1;
}