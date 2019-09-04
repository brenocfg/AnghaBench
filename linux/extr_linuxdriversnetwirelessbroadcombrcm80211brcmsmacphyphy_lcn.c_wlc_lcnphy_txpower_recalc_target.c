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
typedef  int uint ;
typedef  scalar_t__ u32 ;
struct phytbl_info {int tbl_width; int tbl_len; int /*<<< orphan*/  tbl_offset; scalar_t__* tbl_ptr; int /*<<< orphan*/  tbl_id; } ;
struct brcms_phy {scalar_t__ tx_power_min; scalar_t__* tx_power_offset; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int BRCMS_NUM_RATES_CCK ; 
 int BRCMS_NUM_RATES_MCS_1_STREAM ; 
 int BRCMS_NUM_RATES_OFDM ; 
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 int /*<<< orphan*/  LCNPHY_TX_PWR_CTRL_RATE_OFFSET ; 
 int TXP_FIRST_MCS_20_SISO ; 
 scalar_t__ wlc_lcnphy_get_target_tx_pwr (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_target_tx_pwr (struct brcms_phy*,scalar_t__) ; 
 scalar_t__ wlc_lcnphy_tempsense_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_txpower_reset_npt (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

void wlc_lcnphy_txpower_recalc_target(struct brcms_phy *pi)
{
	struct phytbl_info tab;
	u32 rate_table[BRCMS_NUM_RATES_CCK + BRCMS_NUM_RATES_OFDM +
		       BRCMS_NUM_RATES_MCS_1_STREAM];
	uint i, j;
	if (wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi))
		return;

	for (i = 0, j = 0; i < ARRAY_SIZE(rate_table); i++, j++) {

		if (i == BRCMS_NUM_RATES_CCK + BRCMS_NUM_RATES_OFDM)
			j = TXP_FIRST_MCS_20_SISO;

		rate_table[i] = (u32) ((s32) (-pi->tx_power_offset[j]));
	}

	tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
	tab.tbl_width = 32;
	tab.tbl_len = ARRAY_SIZE(rate_table);
	tab.tbl_ptr = rate_table;
	tab.tbl_offset = LCNPHY_TX_PWR_CTRL_RATE_OFFSET;
	wlc_lcnphy_write_table(pi, &tab);

	if (wlc_lcnphy_get_target_tx_pwr(pi) != pi->tx_power_min) {
		wlc_lcnphy_set_target_tx_pwr(pi, pi->tx_power_min);

		wlc_lcnphy_txpower_reset_npt(pi);
	}
}