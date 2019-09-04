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
struct z2_charger {TYPE_1__* info; int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int batt_mult; int batt_div; int /*<<< orphan*/  batt_I2C_reg; } ;

/* Variables and functions */
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long z2_read_bat(struct z2_charger *charger)
{
	int data;
	data = i2c_smbus_read_byte_data(charger->client,
					charger->info->batt_I2C_reg);
	if (data < 0)
		return 0;

	return data * charger->info->batt_mult / charger->info->batt_div;
}