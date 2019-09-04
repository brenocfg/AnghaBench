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
struct fb_info {struct ep93xx_fbi* par; } ;
struct ep93xx_fbi {TYPE_1__* mach_info; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* blank ) (int,struct fb_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XXFB_ATTRIBS ; 
 unsigned int EP93XXFB_ENABLE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xxfb_out_locked (struct ep93xx_fbi*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int ep93xxfb_readl (struct ep93xx_fbi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,struct fb_info*) ; 
 int /*<<< orphan*/  stub2 (int,struct fb_info*) ; 

__attribute__((used)) static int ep93xxfb_blank(int blank_mode, struct fb_info *info)
{
	struct ep93xx_fbi *fbi = info->par;
	unsigned int attribs = ep93xxfb_readl(fbi, EP93XXFB_ATTRIBS);

	if (blank_mode) {
		if (fbi->mach_info->blank)
			fbi->mach_info->blank(blank_mode, info);
		ep93xxfb_out_locked(fbi, attribs & ~EP93XXFB_ENABLE,
				    EP93XXFB_ATTRIBS);
		clk_disable(fbi->clk);
	} else {
		clk_enable(fbi->clk);
		ep93xxfb_out_locked(fbi, attribs | EP93XXFB_ENABLE,
				    EP93XXFB_ATTRIBS);
		if (fbi->mach_info->blank)
			fbi->mach_info->blank(blank_mode, info);
	}

	return 0;
}