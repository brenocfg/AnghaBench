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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSCTRL ; 
 int DSCTRL_SYNCGEN_EN ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  PIXCLK ; 
 int PIXCLK_EN ; 
 int /*<<< orphan*/  VOVRCLK ; 
 int VOVRCLK_EN ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_dly (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mbxfb_blank(int blank, struct fb_info *info)
{
	switch (blank) {
	case FB_BLANK_POWERDOWN:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
		write_reg_dly((readl(DSCTRL) & ~DSCTRL_SYNCGEN_EN), DSCTRL);
		write_reg_dly((readl(PIXCLK) & ~PIXCLK_EN), PIXCLK);
		write_reg_dly((readl(VOVRCLK) & ~VOVRCLK_EN), VOVRCLK);
		break;
	case FB_BLANK_UNBLANK:
		write_reg_dly((readl(DSCTRL) | DSCTRL_SYNCGEN_EN), DSCTRL);
		write_reg_dly((readl(PIXCLK) | PIXCLK_EN), PIXCLK);
		break;
	}
	return 0;
}