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
struct imxfb_info {int enabled; scalar_t__ regs; int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_per; } ;

/* Variables and functions */
 scalar_t__ LCDC_RMCR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imxfb_disable_controller(struct imxfb_info *fbi)
{
	if (!fbi->enabled)
		return;

	pr_debug("Disabling LCD controller\n");

	clk_disable_unprepare(fbi->clk_per);
	clk_disable_unprepare(fbi->clk_ahb);
	clk_disable_unprepare(fbi->clk_ipg);
	fbi->enabled = false;

	writel(0, fbi->regs + LCDC_RMCR);
}