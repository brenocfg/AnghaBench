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
typedef  int u8 ;
typedef  int u32 ;
struct txpower_info_5g {int** index_bw40_base; int** ofdm_diff; int** bw20_diff; int** bw80_diff; int** bw160_diff; int** bw40_diff; } ;
struct txpower_info_2g {int** index_cck_base; int** index_bw40_base; int** bw20_diff; int** ofdm_diff; int** bw40_diff; int** cck_diff; } ;
struct TYPE_2__ {int txpwr_fromeprom; } ;
struct rtl_priv {TYPE_1__ efuse; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EEPROM_TX_PWR_INX ; 
 int MAX_CHNL_GROUP_24G ; 
 int MAX_CHNL_GROUP_5G ; 
 int MAX_RF_PATH ; 
 int MAX_TX_COUNT ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8192ee_read_power_value_fromprom(struct ieee80211_hw *hw,
						 struct txpower_info_2g *pwr2g,
						 struct txpower_info_5g *pwr5g,
						 bool autoload_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 rf, addr = EEPROM_TX_PWR_INX, group, i = 0;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "hal_ReadPowerValueFromPROM92E(): PROMContent[0x%x]=0x%x\n",
		 (addr + 1), hwinfo[addr + 1]);
	if (0xFF == hwinfo[addr+1])  /*YJ,add,120316*/
		autoload_fail = true;

	if (autoload_fail) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "auto load fail : Use Default value!\n");
		for (rf = 0 ; rf < MAX_RF_PATH ; rf++) {
			/* 2.4G default value */
			for (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) {
				pwr2g->index_cck_base[rf][group] = 0x2D;
				pwr2g->index_bw40_base[rf][group] = 0x2D;
			}
			for (i = 0; i < MAX_TX_COUNT; i++) {
				if (i == 0) {
					pwr2g->bw20_diff[rf][0] = 0x02;
					pwr2g->ofdm_diff[rf][0] = 0x04;
				} else {
					pwr2g->bw20_diff[rf][i] = 0xFE;
					pwr2g->bw40_diff[rf][i] = 0xFE;
					pwr2g->cck_diff[rf][i] = 0xFE;
					pwr2g->ofdm_diff[rf][i] = 0xFE;
				}
			}

			/*5G default value*/
			for (group = 0 ; group < MAX_CHNL_GROUP_5G; group++)
				pwr5g->index_bw40_base[rf][group] = 0x2A;

			for (i = 0; i < MAX_TX_COUNT; i++) {
				if (i == 0) {
					pwr5g->ofdm_diff[rf][0] = 0x04;
					pwr5g->bw20_diff[rf][0] = 0x00;
					pwr5g->bw80_diff[rf][0] = 0xFE;
					pwr5g->bw160_diff[rf][0] = 0xFE;
				} else {
					pwr5g->ofdm_diff[rf][0] = 0xFE;
					pwr5g->bw20_diff[rf][0] = 0xFE;
					pwr5g->bw40_diff[rf][0] = 0xFE;
					pwr5g->bw80_diff[rf][0] = 0xFE;
					pwr5g->bw160_diff[rf][0] = 0xFE;
				}
			}
		}
		return;
	}

	rtl_priv(hw)->efuse.txpwr_fromeprom = true;

	for (rf = 0 ; rf < MAX_RF_PATH ; rf++) {
		/*2.4G default value*/
		for (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) {
			pwr2g->index_cck_base[rf][group] = hwinfo[addr++];
			if (pwr2g->index_cck_base[rf][group] == 0xFF)
				pwr2g->index_cck_base[rf][group] = 0x2D;
		}
		for (group = 0 ; group < MAX_CHNL_GROUP_24G - 1; group++) {
			pwr2g->index_bw40_base[rf][group] = hwinfo[addr++];
			if (pwr2g->index_bw40_base[rf][group] == 0xFF)
				pwr2g->index_bw40_base[rf][group] = 0x2D;
		}
		for (i = 0; i < MAX_TX_COUNT; i++) {
			if (i == 0) {
				pwr2g->bw40_diff[rf][i] = 0;
				if (hwinfo[addr] == 0xFF) {
					pwr2g->bw20_diff[rf][i] = 0x02;
				} else {
					pwr2g->bw20_diff[rf][i] = (hwinfo[addr]
								   & 0xf0) >> 4;
					if (pwr2g->bw20_diff[rf][i] & BIT(3))
						pwr2g->bw20_diff[rf][i] |= 0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pwr2g->ofdm_diff[rf][i] = 0x04;
				} else {
					pwr2g->ofdm_diff[rf][i] = (hwinfo[addr]
								   & 0x0f);
					if (pwr2g->ofdm_diff[rf][i] & BIT(3))
						pwr2g->ofdm_diff[rf][i] |= 0xF0;
				}
				pwr2g->cck_diff[rf][i] = 0;
				addr++;
			} else {
				if (hwinfo[addr] == 0xFF) {
					pwr2g->bw40_diff[rf][i] = 0xFE;
				} else {
					pwr2g->bw40_diff[rf][i] = (hwinfo[addr]
								   & 0xf0) >> 4;
					if (pwr2g->bw40_diff[rf][i] & BIT(3))
						pwr2g->bw40_diff[rf][i] |= 0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pwr2g->bw20_diff[rf][i] = 0xFE;
				} else {
					pwr2g->bw20_diff[rf][i] = (hwinfo[addr]
								   & 0x0f);
					if (pwr2g->bw20_diff[rf][i] & BIT(3))
						pwr2g->bw20_diff[rf][i] |= 0xF0;
				}
				addr++;

				if (hwinfo[addr] == 0xFF) {
					pwr2g->ofdm_diff[rf][i] = 0xFE;
				} else {
					pwr2g->ofdm_diff[rf][i] = (hwinfo[addr]
								   & 0xf0) >> 4;
					if (pwr2g->ofdm_diff[rf][i] & BIT(3))
						pwr2g->ofdm_diff[rf][i] |= 0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pwr2g->cck_diff[rf][i] = 0xFE;
				} else {
					pwr2g->cck_diff[rf][i] = (hwinfo[addr]
								  & 0x0f);
					if (pwr2g->cck_diff[rf][i] & BIT(3))
						pwr2g->cck_diff[rf][i] |= 0xF0;
				}
				addr++;
			}
		}

		/*5G default value*/
		for (group = 0 ; group < MAX_CHNL_GROUP_5G; group++) {
			pwr5g->index_bw40_base[rf][group] = hwinfo[addr++];
			if (pwr5g->index_bw40_base[rf][group] == 0xFF)
				pwr5g->index_bw40_base[rf][group] = 0xFE;
		}

		for (i = 0; i < MAX_TX_COUNT; i++) {
			if (i == 0) {
				pwr5g->bw40_diff[rf][i] = 0;

				if (hwinfo[addr] == 0xFF) {
					pwr5g->bw20_diff[rf][i] = 0;
				} else {
					pwr5g->bw20_diff[rf][0] = (hwinfo[addr]
								   & 0xf0) >> 4;
					if (pwr5g->bw20_diff[rf][i] & BIT(3))
						pwr5g->bw20_diff[rf][i] |= 0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pwr5g->ofdm_diff[rf][i] = 0x04;
				} else {
					pwr5g->ofdm_diff[rf][0] = (hwinfo[addr]
								   & 0x0f);
					if (pwr5g->ofdm_diff[rf][i] & BIT(3))
						pwr5g->ofdm_diff[rf][i] |= 0xF0;
				}
				addr++;
			} else {
				if (hwinfo[addr] == 0xFF) {
					pwr5g->bw40_diff[rf][i] = 0xFE;
				} else {
					pwr5g->bw40_diff[rf][i] = (hwinfo[addr]
								  & 0xf0) >> 4;
					if (pwr5g->bw40_diff[rf][i] & BIT(3))
						pwr5g->bw40_diff[rf][i] |= 0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pwr5g->bw20_diff[rf][i] = 0xFE;
				} else {
					pwr5g->bw20_diff[rf][i] = (hwinfo[addr]
								   & 0x0f);
					if (pwr5g->bw20_diff[rf][i] & BIT(3))
						pwr5g->bw20_diff[rf][i] |= 0xF0;
				}
				addr++;
			}
		}

		if (hwinfo[addr] == 0xFF) {
			pwr5g->ofdm_diff[rf][1] = 0xFE;
			pwr5g->ofdm_diff[rf][2] = 0xFE;
		} else {
			pwr5g->ofdm_diff[rf][1] = (hwinfo[addr] & 0xf0) >> 4;
			pwr5g->ofdm_diff[rf][2] = (hwinfo[addr] & 0x0f);
		}
		addr++;

		if (hwinfo[addr] == 0xFF)
			pwr5g->ofdm_diff[rf][3] = 0xFE;
		else
			pwr5g->ofdm_diff[rf][3] = (hwinfo[addr] & 0x0f);
		addr++;

		for (i = 1; i < MAX_TX_COUNT; i++) {
			if (pwr5g->ofdm_diff[rf][i] == 0xFF)
				pwr5g->ofdm_diff[rf][i] = 0xFE;
			else if (pwr5g->ofdm_diff[rf][i] & BIT(3))
				pwr5g->ofdm_diff[rf][i] |= 0xF0;
		}

		for (i = 0; i < MAX_TX_COUNT; i++) {
			if (hwinfo[addr] == 0xFF) {
				pwr5g->bw80_diff[rf][i] = 0xFE;
			} else {
				pwr5g->bw80_diff[rf][i] = (hwinfo[addr] & 0xf0)
							  >> 4;
				if (pwr5g->bw80_diff[rf][i] & BIT(3))
					pwr5g->bw80_diff[rf][i] |= 0xF0;
			}

			if (hwinfo[addr] == 0xFF) {
				pwr5g->bw160_diff[rf][i] = 0xFE;
			} else {
				pwr5g->bw160_diff[rf][i] =
				  (hwinfo[addr] & 0x0f);
				if (pwr5g->bw160_diff[rf][i] & BIT(3))
					pwr5g->bw160_diff[rf][i] |= 0xF0;
			}
			addr++;
		}
	}
}