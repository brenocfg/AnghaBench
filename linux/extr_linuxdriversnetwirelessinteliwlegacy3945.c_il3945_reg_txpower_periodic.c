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
struct TYPE_2__ {int /*<<< orphan*/  thermal_periodic; } ;
struct il_priv {TYPE_1__ _3945; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int HZ ; 
 int REG_RECALIB_PERIOD ; 
 int /*<<< orphan*/  il3945_hw_reg_comp_txpower_temp (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_is_temp_calib_needed (struct il_priv*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
il3945_reg_txpower_periodic(struct il_priv *il)
{
	/* This will kick in the "brute force"
	 * il3945_hw_reg_comp_txpower_temp() below */
	if (!il3945_is_temp_calib_needed(il))
		goto reschedule;

	/* Set up a new set of temp-adjusted TxPowers, send to NIC.
	 * This is based *only* on current temperature,
	 * ignoring any previous power measurements */
	il3945_hw_reg_comp_txpower_temp(il);

reschedule:
	queue_delayed_work(il->workqueue, &il->_3945.thermal_periodic,
			   REG_RECALIB_PERIOD * HZ);
}