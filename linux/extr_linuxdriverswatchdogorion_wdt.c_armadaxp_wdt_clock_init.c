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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct orion_watchdog {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_rate; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TIMER_CTRL ; 
 int /*<<< orphan*/  WDT_AXP_FIXED_ENABLE_BIT ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_get_by_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int armadaxp_wdt_clock_init(struct platform_device *pdev,
				   struct orion_watchdog *dev)
{
	int ret;

	dev->clk = of_clk_get_by_name(pdev->dev.of_node, "fixed");
	if (IS_ERR(dev->clk))
		return PTR_ERR(dev->clk);
	ret = clk_prepare_enable(dev->clk);
	if (ret) {
		clk_put(dev->clk);
		return ret;
	}

	/* Enable the fixed watchdog clock input */
	atomic_io_modify(dev->reg + TIMER_CTRL,
			 WDT_AXP_FIXED_ENABLE_BIT,
			 WDT_AXP_FIXED_ENABLE_BIT);

	dev->clk_rate = clk_get_rate(dev->clk);
	return 0;
}