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
struct TYPE_2__ {int /*<<< orphan*/  ldo1_en; int /*<<< orphan*/  jd_src; int /*<<< orphan*/  dmic1_clk_pin; int /*<<< orphan*/  dmic1_data_pin; } ;
struct rt5668_priv {TYPE_1__ pdata; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt5668_parse_dt(struct rt5668_priv *rt5668, struct device *dev)
{

	of_property_read_u32(dev->of_node, "realtek,dmic1-data-pin",
		&rt5668->pdata.dmic1_data_pin);
	of_property_read_u32(dev->of_node, "realtek,dmic1-clk-pin",
		&rt5668->pdata.dmic1_clk_pin);
	of_property_read_u32(dev->of_node, "realtek,jd-src",
		&rt5668->pdata.jd_src);

	rt5668->pdata.ldo1_en = of_get_named_gpio(dev->of_node,
		"realtek,ldo1-en-gpios", 0);

	return 0;
}