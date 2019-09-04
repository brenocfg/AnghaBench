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
typedef  int s16 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 size_t REG_CURRENT ; 
 TYPE_1__* sbs_data ; 
 int sbs_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbs_status_correct(struct i2c_client *client, int *intval)
{
	int ret;

	ret = sbs_read_word_data(client, sbs_data[REG_CURRENT].addr);
	if (ret < 0)
		return ret;

	ret = (s16)ret;

	/* Not drawing current means full (cannot be not charging) */
	if (ret == 0)
		*intval = POWER_SUPPLY_STATUS_FULL;

	if (*intval == POWER_SUPPLY_STATUS_FULL) {
		/* Drawing or providing current when full */
		if (ret > 0)
			*intval = POWER_SUPPLY_STATUS_CHARGING;
		else if (ret < 0)
			*intval = POWER_SUPPLY_STATUS_DISCHARGING;
	}

	return 0;
}