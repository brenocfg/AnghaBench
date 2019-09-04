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
typedef  int u8 ;
typedef  int u32 ;
struct fb_info {struct arkfb_info* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  vgabase; } ;
struct arkfb_info {TYPE_1__ state; int /*<<< orphan*/  dac; } ;

/* Variables and functions */
 int VGA_MIS_ENB_PLL_LOAD ; 
 int /*<<< orphan*/  VGA_MIS_R ; 
 int /*<<< orphan*/  VGA_MIS_W ; 
 int dac_set_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fb_err (struct fb_info*,char*) ; 
 int vga_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ark_set_pixclock(struct fb_info *info, u32 pixclock)
{
	struct arkfb_info *par = info->par;
	u8 regval;

	int rv = dac_set_freq(par->dac, 0, 1000000000 / pixclock);
	if (rv < 0) {
		fb_err(info, "cannot set requested pixclock, keeping old value\n");
		return;
	}

	/* Set VGA misc register  */
	regval = vga_r(par->state.vgabase, VGA_MIS_R);
	vga_w(par->state.vgabase, VGA_MIS_W, regval | VGA_MIS_ENB_PLL_LOAD);
}