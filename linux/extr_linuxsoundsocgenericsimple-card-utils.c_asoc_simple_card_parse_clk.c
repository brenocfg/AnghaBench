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
typedef  void* u32 ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;
struct asoc_simple_dai {int /*<<< orphan*/  clk_direction; void* sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  asoc_simple_card_clk_register (struct asoc_simple_dai*,struct clk*) ; 
 void* clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*,void*,int /*<<< orphan*/ ) ; 
 struct clk* devm_get_clk_from_child (struct device*,struct device_node*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,void**) ; 

int asoc_simple_card_parse_clk(struct device *dev,
			       struct device_node *node,
			       struct device_node *dai_of_node,
			       struct asoc_simple_dai *simple_dai,
			       const char *name)
{
	struct clk *clk;
	u32 val;

	/*
	 * Parse dai->sysclk come from "clocks = <&xxx>"
	 * (if system has common clock)
	 *  or "system-clock-frequency = <xxx>"
	 *  or device's module clock.
	 */
	clk = devm_get_clk_from_child(dev, node, NULL);
	if (!IS_ERR(clk)) {
		simple_dai->sysclk = clk_get_rate(clk);

		asoc_simple_card_clk_register(simple_dai, clk);
	} else if (!of_property_read_u32(node, "system-clock-frequency", &val)) {
		simple_dai->sysclk = val;
	} else {
		clk = devm_get_clk_from_child(dev, dai_of_node, NULL);
		if (!IS_ERR(clk))
			simple_dai->sysclk = clk_get_rate(clk);
	}

	if (of_property_read_bool(node, "system-clock-direction-out"))
		simple_dai->clk_direction = SND_SOC_CLOCK_OUT;

	dev_dbg(dev, "%s : sysclk = %d, direction %d\n", name,
		simple_dai->sysclk, simple_dai->clk_direction);

	return 0;
}