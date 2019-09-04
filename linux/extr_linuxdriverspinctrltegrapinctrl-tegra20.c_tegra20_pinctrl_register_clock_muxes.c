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
struct tegra_pmx {scalar_t__* regs; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_MUX_READ_ONLY ; 
 int /*<<< orphan*/  cdev1_parents ; 
 int /*<<< orphan*/  cdev2_parents ; 
 int /*<<< orphan*/  clk_register_mux (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tegra_pmx* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void tegra20_pinctrl_register_clock_muxes(struct platform_device *pdev)
{
	struct tegra_pmx *pmx = platform_get_drvdata(pdev);

	clk_register_mux(NULL, "cdev1_mux", cdev1_parents, 4, 0,
			 pmx->regs[1] + 0x8, 2, 2, CLK_MUX_READ_ONLY, NULL);

	clk_register_mux(NULL, "cdev2_mux", cdev2_parents, 4, 0,
			 pmx->regs[1] + 0x8, 4, 2, CLK_MUX_READ_ONLY, NULL);
}