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
struct TYPE_2__ {int /*<<< orphan*/  ldo1_en; int /*<<< orphan*/  jd_src; int /*<<< orphan*/  dmic2_data_pin; int /*<<< orphan*/  dmic1_data_pin; void* in4_diff; void* in3_diff; void* in2_diff; void* in1_diff; } ;
struct rt5665_priv {TYPE_1__ pdata; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt5665_parse_dt(struct rt5665_priv *rt5665, struct device *dev)
{
	rt5665->pdata.in1_diff = of_property_read_bool(dev->of_node,
					"realtek,in1-differential");
	rt5665->pdata.in2_diff = of_property_read_bool(dev->of_node,
					"realtek,in2-differential");
	rt5665->pdata.in3_diff = of_property_read_bool(dev->of_node,
					"realtek,in3-differential");
	rt5665->pdata.in4_diff = of_property_read_bool(dev->of_node,
					"realtek,in4-differential");

	of_property_read_u32(dev->of_node, "realtek,dmic1-data-pin",
		&rt5665->pdata.dmic1_data_pin);
	of_property_read_u32(dev->of_node, "realtek,dmic2-data-pin",
		&rt5665->pdata.dmic2_data_pin);
	of_property_read_u32(dev->of_node, "realtek,jd-src",
		&rt5665->pdata.jd_src);

	rt5665->pdata.ldo1_en = of_get_named_gpio(dev->of_node,
		"realtek,ldo1-en-gpios", 0);

	return 0;
}