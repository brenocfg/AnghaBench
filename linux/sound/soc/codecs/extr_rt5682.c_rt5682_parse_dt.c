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
struct rt5682_priv {TYPE_1__ pdata; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5682_parse_dt(struct rt5682_priv *rt5682, struct device *dev)
{

	device_property_read_u32(dev, "realtek,dmic1-data-pin",
		&rt5682->pdata.dmic1_data_pin);
	device_property_read_u32(dev, "realtek,dmic1-clk-pin",
		&rt5682->pdata.dmic1_clk_pin);
	device_property_read_u32(dev, "realtek,jd-src",
		&rt5682->pdata.jd_src);

	rt5682->pdata.ldo1_en = of_get_named_gpio(dev->of_node,
		"realtek,ldo1-en-gpios", 0);

	return 0;
}