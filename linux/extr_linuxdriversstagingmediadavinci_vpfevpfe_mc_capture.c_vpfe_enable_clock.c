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
struct vpfe_device {int /*<<< orphan*/ * clks; TYPE_1__* pdev; struct vpfe_config* cfg; } ;
struct vpfe_config {int num_clocks; int /*<<< orphan*/ ** clocks; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vpfe_enable_clock(struct vpfe_device *vpfe_dev)
{
	struct vpfe_config *vpfe_cfg = vpfe_dev->cfg;
	int ret = -EFAULT;
	int i;

	if (!vpfe_cfg->num_clocks)
		return 0;

	vpfe_dev->clks = kcalloc(vpfe_cfg->num_clocks,
				 sizeof(*vpfe_dev->clks), GFP_KERNEL);
	if (!vpfe_dev->clks)
		return -ENOMEM;

	for (i = 0; i < vpfe_cfg->num_clocks; i++) {
		if (vpfe_cfg->clocks[i] == NULL) {
			v4l2_err(vpfe_dev->pdev->driver,
				"clock %s is not defined in vpfe config\n",
				vpfe_cfg->clocks[i]);
			goto out;
		}

		vpfe_dev->clks[i] =
				clk_get(vpfe_dev->pdev, vpfe_cfg->clocks[i]);
		if (IS_ERR(vpfe_dev->clks[i])) {
			v4l2_err(vpfe_dev->pdev->driver,
				"Failed to get clock %s\n",
				vpfe_cfg->clocks[i]);
			goto out;
		}

		if (clk_prepare_enable(vpfe_dev->clks[i])) {
			v4l2_err(vpfe_dev->pdev->driver,
				"vpfe clock %s not enabled\n",
				vpfe_cfg->clocks[i]);
			goto out;
		}

		v4l2_info(vpfe_dev->pdev->driver, "vpss clock %s enabled",
			  vpfe_cfg->clocks[i]);
	}

	return 0;
out:
	for (i = 0; i < vpfe_cfg->num_clocks; i++)
		if (!IS_ERR(vpfe_dev->clks[i])) {
			clk_disable_unprepare(vpfe_dev->clks[i]);
			clk_put(vpfe_dev->clks[i]);
		}

	v4l2_err(vpfe_dev->pdev->driver, "Failed to enable clocks\n");
	kzfree(vpfe_dev->clks);

	return ret;
}