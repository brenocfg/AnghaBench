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
struct st_slim_rproc {int /*<<< orphan*/ ** clks; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int ST_SLIM_MAX_CLK ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_clk_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int slim_clk_get(struct st_slim_rproc *slim_rproc, struct device *dev)
{
	int clk, err;

	for (clk = 0; clk < ST_SLIM_MAX_CLK; clk++) {
		slim_rproc->clks[clk] = of_clk_get(dev->of_node, clk);
		if (IS_ERR(slim_rproc->clks[clk])) {
			err = PTR_ERR(slim_rproc->clks[clk]);
			if (err == -EPROBE_DEFER)
				goto err_put_clks;
			slim_rproc->clks[clk] = NULL;
			break;
		}
	}

	return 0;

err_put_clks:
	while (--clk >= 0)
		clk_put(slim_rproc->clks[clk]);

	return err;
}