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
struct dwc3_of_simple {int num_clocks; struct clk** clks; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 struct clk** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct clk* of_clk_get (struct device_node*,int) ; 

__attribute__((used)) static int dwc3_of_simple_clk_init(struct dwc3_of_simple *simple, int count)
{
	struct device		*dev = simple->dev;
	struct device_node	*np = dev->of_node;
	int			i;

	simple->num_clocks = count;

	if (!count)
		return 0;

	simple->clks = devm_kcalloc(dev, simple->num_clocks,
			sizeof(struct clk *), GFP_KERNEL);
	if (!simple->clks)
		return -ENOMEM;

	for (i = 0; i < simple->num_clocks; i++) {
		struct clk	*clk;
		int		ret;

		clk = of_clk_get(np, i);
		if (IS_ERR(clk)) {
			while (--i >= 0) {
				clk_disable_unprepare(simple->clks[i]);
				clk_put(simple->clks[i]);
			}
			return PTR_ERR(clk);
		}

		ret = clk_prepare_enable(clk);
		if (ret < 0) {
			while (--i >= 0) {
				clk_disable_unprepare(simple->clks[i]);
				clk_put(simple->clks[i]);
			}
			clk_put(clk);

			return ret;
		}

		simple->clks[i] = clk;
	}

	return 0;
}