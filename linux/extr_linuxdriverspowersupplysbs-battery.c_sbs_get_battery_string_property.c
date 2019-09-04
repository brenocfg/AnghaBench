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
struct i2c_client {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 TYPE_1__* sbs_data ; 
 scalar_t__ sbs_read_string_data (struct i2c_client*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sbs_get_battery_string_property(struct i2c_client *client,
	int reg_offset, enum power_supply_property psp, char *val)
{
	s32 ret;

	ret = sbs_read_string_data(client, sbs_data[reg_offset].addr, val);

	if (ret < 0)
		return ret;

	return 0;
}