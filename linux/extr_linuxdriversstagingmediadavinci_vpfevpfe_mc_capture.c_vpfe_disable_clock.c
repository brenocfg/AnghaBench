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
struct vpfe_device {TYPE_1__* pdev; int /*<<< orphan*/ * clks; struct vpfe_config* cfg; } ;
struct vpfe_config {int num_clocks; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void vpfe_disable_clock(struct vpfe_device *vpfe_dev)
{
	struct vpfe_config *vpfe_cfg = vpfe_dev->cfg;
	int i;

	for (i = 0; i < vpfe_cfg->num_clocks; i++) {
		clk_disable_unprepare(vpfe_dev->clks[i]);
		clk_put(vpfe_dev->clks[i]);
	}
	kzfree(vpfe_dev->clks);
	v4l2_info(vpfe_dev->pdev->driver, "vpfe capture clocks disabled\n");
}