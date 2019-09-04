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
struct il_priv {scalar_t__ temperature; int /*<<< orphan*/  txpower_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; int /*<<< orphan*/  disable_tx_power_cal; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_TEMP (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ IL_TX_POWER_TEMPERATURE_OUT_OF_RANGE (scalar_t__) ; 
 int /*<<< orphan*/  KELVIN_TO_CELSIUS (scalar_t__) ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  S_TEMPERATURE ; 
 scalar_t__ il4965_hw_get_temperature (struct il_priv*) ; 
 scalar_t__ il4965_is_temp_calib_needed (struct il_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void
il4965_temperature_calib(struct il_priv *il)
{
	s32 temp;

	temp = il4965_hw_get_temperature(il);
	if (IL_TX_POWER_TEMPERATURE_OUT_OF_RANGE(temp))
		return;

	if (il->temperature != temp) {
		if (il->temperature)
			D_TEMP("Temperature changed " "from %dC to %dC\n",
			       KELVIN_TO_CELSIUS(il->temperature),
			       KELVIN_TO_CELSIUS(temp));
		else
			D_TEMP("Temperature " "initialized to %dC\n",
			       KELVIN_TO_CELSIUS(temp));
	}

	il->temperature = temp;
	set_bit(S_TEMPERATURE, &il->status);

	if (!il->disable_tx_power_cal &&
	    unlikely(!test_bit(S_SCANNING, &il->status)) &&
	    il4965_is_temp_calib_needed(il))
		queue_work(il->workqueue, &il->txpower_work);
}