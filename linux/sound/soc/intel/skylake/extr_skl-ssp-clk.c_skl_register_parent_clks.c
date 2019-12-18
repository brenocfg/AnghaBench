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
struct skl_clk_parent_src {int /*<<< orphan*/  name; int /*<<< orphan*/  rate; int /*<<< orphan*/  parent_name; } ;
struct skl_clk_parent {int /*<<< orphan*/  hw; int /*<<< orphan*/  lookup; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SKL_MAX_CLK_SRC ; 
 int /*<<< orphan*/  clk_hw_register_fixed_rate (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_fixed_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_hw_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_parent_src_clk (struct skl_clk_parent*,int) ; 

__attribute__((used)) static int skl_register_parent_clks(struct device *dev,
			struct skl_clk_parent *parent,
			struct skl_clk_parent_src *pclk)
{
	int i, ret;

	for (i = 0; i < SKL_MAX_CLK_SRC; i++) {

		/* Register Parent clock */
		parent[i].hw = clk_hw_register_fixed_rate(dev, pclk[i].name,
				pclk[i].parent_name, 0, pclk[i].rate);
		if (IS_ERR(parent[i].hw)) {
			ret = PTR_ERR(parent[i].hw);
			goto err;
		}

		parent[i].lookup = clkdev_hw_create(parent[i].hw, pclk[i].name,
									NULL);
		if (!parent[i].lookup) {
			clk_hw_unregister_fixed_rate(parent[i].hw);
			ret = -ENOMEM;
			goto err;
		}
	}

	return 0;
err:
	unregister_parent_src_clk(parent, i);
	return ret;
}