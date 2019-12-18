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
struct TYPE_2__ {int dc_offset_l_manual; int dc_offset_r_manual; int dc_offset_l_manual_mic; int dc_offset_r_manual_mic; int impedance_sensing_num; } ;
struct rt5663_priv {scalar_t__ imp_table; TYPE_1__ pdata; } ;
struct impedance_mapping_table {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  device_property_read_u32_array (struct device*,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5663_parse_dp(struct rt5663_priv *rt5663, struct device *dev)
{
	int table_size;

	device_property_read_u32(dev, "realtek,dc_offset_l_manual",
		&rt5663->pdata.dc_offset_l_manual);
	device_property_read_u32(dev, "realtek,dc_offset_r_manual",
		&rt5663->pdata.dc_offset_r_manual);
	device_property_read_u32(dev, "realtek,dc_offset_l_manual_mic",
		&rt5663->pdata.dc_offset_l_manual_mic);
	device_property_read_u32(dev, "realtek,dc_offset_r_manual_mic",
		&rt5663->pdata.dc_offset_r_manual_mic);
	device_property_read_u32(dev, "realtek,impedance_sensing_num",
		&rt5663->pdata.impedance_sensing_num);

	if (rt5663->pdata.impedance_sensing_num) {
		table_size = sizeof(struct impedance_mapping_table) *
			rt5663->pdata.impedance_sensing_num;
		rt5663->imp_table = devm_kzalloc(dev, table_size, GFP_KERNEL);
		device_property_read_u32_array(dev,
			"realtek,impedance_sensing_table",
			(u32 *)rt5663->imp_table, table_size);
	}

	return 0;
}