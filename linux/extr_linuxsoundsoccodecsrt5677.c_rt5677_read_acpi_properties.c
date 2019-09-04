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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  jd3_gpio; int /*<<< orphan*/  jd2_gpio; int /*<<< orphan*/  jd1_gpio; void* lout3_diff; void* lout2_diff; void* lout1_diff; void* in2_diff; void* in1_diff; int /*<<< orphan*/  dmic2_clk_pin; } ;
struct rt5677_priv {TYPE_1__ pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt5677_read_acpi_properties(struct rt5677_priv *rt5677,
		struct device *dev)
{
	u32 val;

	if (!device_property_read_u32(dev, "DCLK", &val))
		rt5677->pdata.dmic2_clk_pin = val;

	rt5677->pdata.in1_diff = device_property_read_bool(dev, "IN1");
	rt5677->pdata.in2_diff = device_property_read_bool(dev, "IN2");
	rt5677->pdata.lout1_diff = device_property_read_bool(dev, "OUT1");
	rt5677->pdata.lout2_diff = device_property_read_bool(dev, "OUT2");
	rt5677->pdata.lout3_diff = device_property_read_bool(dev, "OUT3");

	device_property_read_u32(dev, "JD1", &rt5677->pdata.jd1_gpio);
	device_property_read_u32(dev, "JD2", &rt5677->pdata.jd2_gpio);
	device_property_read_u32(dev, "JD3", &rt5677->pdata.jd3_gpio);
}