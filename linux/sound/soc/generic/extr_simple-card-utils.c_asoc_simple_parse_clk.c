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
struct snd_soc_dai_link_component {struct device_node* of_node; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;
struct asoc_simple_dai {int /*<<< orphan*/  clk_direction; void* sysclk; struct clk* clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_OUT ; 
 void* clk_get_rate (struct clk*) ; 
 struct clk* devm_get_clk_from_child (struct device*,struct device_node*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,void**) ; 

int asoc_simple_parse_clk(struct device *dev,
			  struct device_node *node,
			  struct asoc_simple_dai *simple_dai,
			  struct snd_soc_dai_link_component *dlc)
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

		simple_dai->clk = clk;
	} else if (!of_property_read_u32(node, "system-clock-frequency", &val)) {
		simple_dai->sysclk = val;
	} else {
		clk = devm_get_clk_from_child(dev, dlc->of_node, NULL);
		if (!IS_ERR(clk))
			simple_dai->sysclk = clk_get_rate(clk);
	}

	if (of_property_read_bool(node, "system-clock-direction-out"))
		simple_dai->clk_direction = SND_SOC_CLOCK_OUT;

	return 0;
}