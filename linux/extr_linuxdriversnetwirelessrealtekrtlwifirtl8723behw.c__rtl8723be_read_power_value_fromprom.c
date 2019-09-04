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
typedef  int u32 ;
struct txpower_info_5g {int** index_bw40_base; int** bw40_diff; int** bw20_diff; int** ofdm_diff; } ;
struct txpower_info_2g {int** index_cck_base; int** index_bw40_base; int** bw20_diff; int** ofdm_diff; int** bw40_diff; int** cck_diff; } ;
struct rtl_priv {int dummy; } ;
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

__attribute__((used)) static void _rtl8723be_read_power_value_fromprom(struct ieee80211_hw *hw,
					struct txpower_info_2g *pw2g,
					struct txpower_info_5g *pw5g,
					bool autoload_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 path, addr = EEPROM_TX_PWR_INX, group, cnt = 0;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "hal_ReadPowerValueFromPROM8723BE(): PROMContent[0x%x]=0x%x\n",
		 (addr + 1), hwinfo[addr + 1]);
	if (0xFF == hwinfo[addr + 1])  /*YJ,add,120316*/
		autoload_fail = true;

	if (autoload_fail) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "auto load fail : Use Default value!\n");
		for (path = 0; path < MAX_RF_PATH; path++) {
			/* 2.4G default value */
			for (group = 0 ; group < MAX_CHNL_GROUP_24G; group++) {
				pw2g->index_cck_base[path][group] = 0x2D;
				pw2g->index_bw40_base[path][group] = 0x2D;
			}
			for (cnt = 0; cnt < MAX_TX_COUNT; cnt++) {
				if (cnt == 0) {
					pw2g->bw20_diff[path][0] = 0x02;
					pw2g->ofdm_diff[path][0] = 0x04;
				} else {
					pw2g->bw20_diff[path][cnt] = 0xFE;
					pw2g->bw40_diff[path][cnt] = 0xFE;
					pw2g->cck_diff[path][cnt] = 0xFE;
					pw2g->ofdm_diff[path][cnt] = 0xFE;
				}
			}
		}
		return;
	}

	for (path = 0; path < MAX_RF_PATH; path++) {
		/*2.4G default value*/
		for (group = 0; group < MAX_CHNL_GROUP_24G; group++) {
			pw2g->index_cck_base[path][group] = hwinfo[addr++];
			if (pw2g->index_cck_base[path][group] == 0xFF)
				pw2g->index_cck_base[path][group] = 0x2D;

		}
		for (group = 0; group < MAX_CHNL_GROUP_24G - 1; group++) {
			pw2g->index_bw40_base[path][group] = hwinfo[addr++];
			if (pw2g->index_bw40_base[path][group] == 0xFF)
				pw2g->index_bw40_base[path][group] = 0x2D;
		}
		for (cnt = 0; cnt < MAX_TX_COUNT; cnt++) {
			if (cnt == 0) {
				pw2g->bw40_diff[path][cnt] = 0;
				if (hwinfo[addr] == 0xFF) {
					pw2g->bw20_diff[path][cnt] = 0x02;
				} else {
					pw2g->bw20_diff[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					/*bit sign number to 8 bit sign number*/
					if (pw2g->bw20_diff[path][cnt] & BIT(3))
						pw2g->bw20_diff[path][cnt] |=
									  0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pw2g->ofdm_diff[path][cnt] = 0x04;
				} else {
					pw2g->ofdm_diff[path][cnt] =
							(hwinfo[addr] & 0x0f);
					/*bit sign number to 8 bit sign number*/
					if (pw2g->ofdm_diff[path][cnt] & BIT(3))
						pw2g->ofdm_diff[path][cnt] |=
									  0xF0;
				}
				pw2g->cck_diff[path][cnt] = 0;
				addr++;
			} else {
				if (hwinfo[addr] == 0xFF) {
					pw2g->bw40_diff[path][cnt] = 0xFE;
				} else {
					pw2g->bw40_diff[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					if (pw2g->bw40_diff[path][cnt] & BIT(3))
						pw2g->bw40_diff[path][cnt] |=
									  0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pw2g->bw20_diff[path][cnt] = 0xFE;
				} else {
					pw2g->bw20_diff[path][cnt] =
							(hwinfo[addr] & 0x0f);
					if (pw2g->bw20_diff[path][cnt] & BIT(3))
						pw2g->bw20_diff[path][cnt] |=
									  0xF0;
				}
				addr++;

				if (hwinfo[addr] == 0xFF) {
					pw2g->ofdm_diff[path][cnt] = 0xFE;
				} else {
					pw2g->ofdm_diff[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					if (pw2g->ofdm_diff[path][cnt] & BIT(3))
						pw2g->ofdm_diff[path][cnt] |=
									  0xF0;
				}

				if (hwinfo[addr] == 0xFF)
					pw2g->cck_diff[path][cnt] = 0xFE;
				else {
					pw2g->cck_diff[path][cnt] =
							(hwinfo[addr] & 0x0f);
					if (pw2g->cck_diff[path][cnt] & BIT(3))
						pw2g->cck_diff[path][cnt] |=
									 0xF0;
				}
				addr++;
			}
		}

		/*5G default value*/
		for (group = 0; group < MAX_CHNL_GROUP_5G; group++) {
			pw5g->index_bw40_base[path][group] = hwinfo[addr++];
			if (pw5g->index_bw40_base[path][group] == 0xFF)
				pw5g->index_bw40_base[path][group] = 0xFE;
		}

		for (cnt = 0; cnt < MAX_TX_COUNT; cnt++) {
			if (cnt == 0) {
				pw5g->bw40_diff[path][cnt] = 0;

				if (hwinfo[addr] == 0xFF) {
					pw5g->bw20_diff[path][cnt] = 0;
				} else {
					pw5g->bw20_diff[path][0] =
						(hwinfo[addr] & 0xf0) >> 4;
					if (pw5g->bw20_diff[path][cnt] & BIT(3))
						pw5g->bw20_diff[path][cnt] |=
									  0xF0;
				}

				if (hwinfo[addr] == 0xFF)
					pw5g->ofdm_diff[path][cnt] = 0x04;
				else {
					pw5g->ofdm_diff[path][0] =
							(hwinfo[addr] & 0x0f);
					if (pw5g->ofdm_diff[path][cnt] & BIT(3))
						pw5g->ofdm_diff[path][cnt] |=
									  0xF0;
				}
				addr++;
			} else {
				if (hwinfo[addr] == 0xFF) {
					pw5g->bw40_diff[path][cnt] = 0xFE;
				} else {
					pw5g->bw40_diff[path][cnt] =
						(hwinfo[addr] & 0xf0) >> 4;
					if (pw5g->bw40_diff[path][cnt] & BIT(3))
						pw5g->bw40_diff[path][cnt] |= 0xF0;
				}

				if (hwinfo[addr] == 0xFF) {
					pw5g->bw20_diff[path][cnt] = 0xFE;
				} else {
					pw5g->bw20_diff[path][cnt] =
							(hwinfo[addr] & 0x0f);
					if (pw5g->bw20_diff[path][cnt] & BIT(3))
						pw5g->bw20_diff[path][cnt] |= 0xF0;
				}
				addr++;
			}
		}

		if (hwinfo[addr] == 0xFF) {
			pw5g->ofdm_diff[path][1] = 0xFE;
			pw5g->ofdm_diff[path][2] = 0xFE;
		} else {
			pw5g->ofdm_diff[path][1] = (hwinfo[addr] & 0xf0) >> 4;
			pw5g->ofdm_diff[path][2] = (hwinfo[addr] & 0x0f);
		}
		addr++;

		if (hwinfo[addr] == 0xFF)
			pw5g->ofdm_diff[path][3] = 0xFE;
		else
			pw5g->ofdm_diff[path][3] = (hwinfo[addr] & 0x0f);
		addr++;

		for (cnt = 1; cnt < MAX_TX_COUNT; cnt++) {
			if (pw5g->ofdm_diff[path][cnt] == 0xFF)
				pw5g->ofdm_diff[path][cnt] = 0xFE;
			else if (pw5g->ofdm_diff[path][cnt] & BIT(3))
				pw5g->ofdm_diff[path][cnt] |= 0xF0;
		}
	}
}