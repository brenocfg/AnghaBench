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
union power_supply_propval {int /*<<< orphan*/  strval; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 size_t REG_SERIAL_NUMBER ; 
 TYPE_1__* sbs_data ; 
 int sbs_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbs_serial ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int sbs_get_battery_serial_number(struct i2c_client *client,
	union power_supply_propval *val)
{
	int ret;

	ret = sbs_read_word_data(client, sbs_data[REG_SERIAL_NUMBER].addr);
	if (ret < 0)
		return ret;

	sprintf(sbs_serial, "%04x", ret);
	val->strval = sbs_serial;

	return 0;
}