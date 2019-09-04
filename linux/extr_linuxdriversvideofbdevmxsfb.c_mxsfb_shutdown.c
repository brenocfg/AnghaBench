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
struct platform_device {int dummy; } ;
struct mxsfb_info {scalar_t__ base; } ;
struct fb_info {struct mxsfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_RUN ; 
 scalar_t__ LCDC_CTRL ; 
 scalar_t__ REG_CLR ; 
 int /*<<< orphan*/  mxsfb_disable_axi_clk (struct mxsfb_info*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_info*) ; 
 struct fb_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxsfb_shutdown(struct platform_device *pdev)
{
	struct fb_info *fb_info = platform_get_drvdata(pdev);
	struct mxsfb_info *host = fb_info->par;

	mxsfb_enable_axi_clk(host);

	/*
	 * Force stop the LCD controller as keeping it running during reboot
	 * might interfere with the BootROM's boot mode pads sampling.
	 */
	writel(CTRL_RUN, host->base + LCDC_CTRL + REG_CLR);

	mxsfb_disable_axi_clk(host);
}