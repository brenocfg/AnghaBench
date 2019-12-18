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
struct TYPE_2__ {int /*<<< orphan*/  dmic1_data_pin; void* poweroff_codec_in_suspend; void* in3_diff; void* in1_diff; } ;
struct rt5660_priv {TYPE_1__ pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* device_property_read_bool (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt5660_parse_dt(struct rt5660_priv *rt5660, struct device *dev)
{
	rt5660->pdata.in1_diff = device_property_read_bool(dev,
					"realtek,in1-differential");
	rt5660->pdata.in3_diff = device_property_read_bool(dev,
					"realtek,in3-differential");
	rt5660->pdata.poweroff_codec_in_suspend = device_property_read_bool(dev,
					"realtek,poweroff-in-suspend");
	device_property_read_u32(dev, "realtek,dmic1-data-pin",
		&rt5660->pdata.dmic1_data_pin);

	return 0;
}