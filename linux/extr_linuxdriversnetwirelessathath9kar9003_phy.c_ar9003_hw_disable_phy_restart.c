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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int bb_hang_rx_ofdm; int /*<<< orphan*/  bb_watchdog_last_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RESTART ; 
 int /*<<< orphan*/  AR_PHY_RESTART_ENA ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_RX_OFDM_SM ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9003_hw_disable_phy_restart(struct ath_hw *ah)
{
	u8 result;
	u32 val;

	/* While receiving unsupported rate frame rx state machine
	 * gets into a state 0xb and if phy_restart happens in that
	 * state, BB would go hang. If RXSM is in 0xb state after
	 * first bb panic, ensure to disable the phy_restart.
	 */
	result = MS(ah->bb_watchdog_last_status, AR_PHY_WATCHDOG_RX_OFDM_SM);

	if ((result == 0xb) || ah->bb_hang_rx_ofdm) {
		ah->bb_hang_rx_ofdm = true;
		val = REG_READ(ah, AR_PHY_RESTART);
		val &= ~AR_PHY_RESTART_ENA;
		REG_WRITE(ah, AR_PHY_RESTART, val);
	}
}