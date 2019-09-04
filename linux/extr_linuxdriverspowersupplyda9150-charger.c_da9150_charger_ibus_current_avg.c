#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union power_supply_propval {int intval; } ;
struct da9150_charger {int /*<<< orphan*/  ibus_chan; } ;

/* Variables and functions */
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int da9150_charger_ibus_current_avg(struct da9150_charger *charger,
					   union power_supply_propval *val)
{
	int i_val, ret;

	/* Read processed value - mA units */
	ret = iio_read_channel_processed(charger->ibus_chan, &i_val);
	if (ret < 0)
		return ret;

	/* Convert current to expected uA units */
	val->intval = i_val * 1000;

	return 0;
}