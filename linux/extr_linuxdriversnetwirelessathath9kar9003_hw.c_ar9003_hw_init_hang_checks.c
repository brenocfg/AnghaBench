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
struct TYPE_2__ {int /*<<< orphan*/  hw_hang_checks; } ;
struct ath_hw {int bb_watchdog_timeout_ms; TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9300_22 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 int /*<<< orphan*/  HW_BB_WATCHDOG ; 
 int /*<<< orphan*/  HW_MAC_HANG ; 
 int /*<<< orphan*/  HW_PHYRESTART_CLC_WAR ; 

__attribute__((used)) static void ar9003_hw_init_hang_checks(struct ath_hw *ah)
{
	/*
	 * All chips support detection of BB/MAC hangs.
	 */
	ah->config.hw_hang_checks |= HW_BB_WATCHDOG;
	ah->config.hw_hang_checks |= HW_MAC_HANG;

	/*
	 * This is not required for AR9580 1.0
	 */
	if (AR_SREV_9300_22(ah))
		ah->config.hw_hang_checks |= HW_PHYRESTART_CLC_WAR;

	if (AR_SREV_9330(ah))
		ah->bb_watchdog_timeout_ms = 85;
	else
		ah->bb_watchdog_timeout_ms = 25;
}