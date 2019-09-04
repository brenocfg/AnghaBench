#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  toggleq; } ;
struct TYPE_4__ {int /*<<< orphan*/  ee_header; } ;
struct TYPE_5__ {TYPE_1__ cap_eeprom; } ;
struct ath5k_hw {TYPE_3__ rf_kill; TYPE_2__ ah_capabilities; } ;

/* Variables and functions */
 scalar_t__ AR5K_EEPROM_HDR_RFKILL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_rfkill_enable (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_rfkill_set_intr (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void
ath5k_rfkill_hw_stop(struct ath5k_hw *ah)
{
	/* disable interrupt for rfkill switch */
	if (AR5K_EEPROM_HDR_RFKILL(ah->ah_capabilities.cap_eeprom.ee_header))
		ath5k_rfkill_set_intr(ah, false);

	tasklet_kill(&ah->rf_kill.toggleq);

	/* enable RFKILL when stopping HW so Wifi LED is turned off */
	ath5k_rfkill_enable(ah);
}