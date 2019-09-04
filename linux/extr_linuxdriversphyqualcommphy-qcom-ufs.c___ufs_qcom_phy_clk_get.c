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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int) ; 
 struct clk* devm_clk_get (struct device*,char const*) ; 

__attribute__((used)) static int __ufs_qcom_phy_clk_get(struct device *dev,
			 const char *name, struct clk **clk_out, bool err_print)
{
	struct clk *clk;
	int err = 0;

	clk = devm_clk_get(dev, name);
	if (IS_ERR(clk)) {
		err = PTR_ERR(clk);
		if (err_print)
			dev_err(dev, "failed to get %s err %d", name, err);
	} else {
		*clk_out = clk;
	}

	return err;
}