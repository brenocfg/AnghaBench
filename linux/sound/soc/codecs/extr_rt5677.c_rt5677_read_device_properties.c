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
typedef  void* u32 ;
struct TYPE_2__ {int in1_diff; int in2_diff; int lout1_diff; int lout2_diff; int lout3_diff; void* jd3_gpio; void* jd2_gpio; void* jd1_gpio; void* dmic2_clk_pin; int /*<<< orphan*/  gpio_config; } ;
struct rt5677_priv {TYPE_1__ pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5677_GPIO_NUM ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,void**) ; 
 int /*<<< orphan*/  device_property_read_u8_array (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5677_read_device_properties(struct rt5677_priv *rt5677,
		struct device *dev)
{
	u32 val;

	rt5677->pdata.in1_diff =
		device_property_read_bool(dev, "IN1") ||
		device_property_read_bool(dev, "realtek,in1-differential");

	rt5677->pdata.in2_diff =
		device_property_read_bool(dev, "IN2") ||
		device_property_read_bool(dev, "realtek,in2-differential");

	rt5677->pdata.lout1_diff =
		device_property_read_bool(dev, "OUT1") ||
		device_property_read_bool(dev, "realtek,lout1-differential");

	rt5677->pdata.lout2_diff =
		device_property_read_bool(dev, "OUT2") ||
		device_property_read_bool(dev, "realtek,lout2-differential");

	rt5677->pdata.lout3_diff =
		device_property_read_bool(dev, "OUT3") ||
		device_property_read_bool(dev, "realtek,lout3-differential");

	device_property_read_u8_array(dev, "realtek,gpio-config",
				      rt5677->pdata.gpio_config,
				      RT5677_GPIO_NUM);

	if (!device_property_read_u32(dev, "DCLK", &val) ||
	    !device_property_read_u32(dev, "realtek,dmic2_clk_pin", &val))
		rt5677->pdata.dmic2_clk_pin = val;

	if (!device_property_read_u32(dev, "JD1", &val) ||
	    !device_property_read_u32(dev, "realtek,jd1-gpio", &val))
		rt5677->pdata.jd1_gpio = val;

	if (!device_property_read_u32(dev, "JD2", &val) ||
	    !device_property_read_u32(dev, "realtek,jd2-gpio", &val))
		rt5677->pdata.jd2_gpio = val;

	if (!device_property_read_u32(dev, "JD3", &val) ||
	    !device_property_read_u32(dev, "realtek,jd3-gpio", &val))
		rt5677->pdata.jd3_gpio = val;
}