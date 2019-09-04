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
struct fb_info {struct cirrusfb_info* par; } ;
struct cirrusfb_info {int /*<<< orphan*/  regbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_GR31 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  is_laguna (struct cirrusfb_info*) ; 
 int vga_rgfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cirrusfb_sync(struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;

	if (!is_laguna(cinfo)) {
		while (vga_rgfx(cinfo->regbase, CL_GR31) & 0x03)
			cpu_relax();
	}
	return 0;
}