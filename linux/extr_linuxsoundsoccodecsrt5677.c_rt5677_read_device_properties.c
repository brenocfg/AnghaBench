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
struct TYPE_2__ {int /*<<< orphan*/  jd3_gpio; int /*<<< orphan*/  jd2_gpio; int /*<<< orphan*/  jd1_gpio; int /*<<< orphan*/  gpio_config; void* lout3_diff; void* lout2_diff; void* lout1_diff; void* in2_diff; void* in1_diff; } ;
struct rt5677_priv {TYPE_1__ pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5677_GPIO_NUM ; 
 void* device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_property_read_u8_array (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5677_read_device_properties(struct rt5677_priv *rt5677,
		struct device *dev)
{
	rt5677->pdata.in1_diff = device_property_read_bool(dev,
			"realtek,in1-differential");
	rt5677->pdata.in2_diff = device_property_read_bool(dev,
			"realtek,in2-differential");
	rt5677->pdata.lout1_diff = device_property_read_bool(dev,
			"realtek,lout1-differential");
	rt5677->pdata.lout2_diff = device_property_read_bool(dev,
			"realtek,lout2-differential");
	rt5677->pdata.lout3_diff = device_property_read_bool(dev,
			"realtek,lout3-differential");

	device_property_read_u8_array(dev, "realtek,gpio-config",
			rt5677->pdata.gpio_config, RT5677_GPIO_NUM);

	device_property_read_u32(dev, "realtek,jd1-gpio",
			&rt5677->pdata.jd1_gpio);
	device_property_read_u32(dev, "realtek,jd2-gpio",
			&rt5677->pdata.jd2_gpio);
	device_property_read_u32(dev, "realtek,jd3-gpio",
			&rt5677->pdata.jd3_gpio);
}