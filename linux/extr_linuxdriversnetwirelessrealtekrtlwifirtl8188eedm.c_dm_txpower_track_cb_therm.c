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
struct TYPE_2__ {int txpower_trackinginit; int thermalvalue; int thermalvalue_lck; int thermalvalue_iqk; int* ofdm_index; int cck_index; int done_txpower; scalar_t__ txpower_track_control; scalar_t__ cck_inch14; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct rtl_hal {int reloadtxpowerindex; } ;
struct rtl_efuse {int eeprom_thermalmeter; } ;
struct rtl_dm {int* swing_idx_ofdm_base; int swing_idx_cck_base; int thermalvalue; int* thermalvalue_avg; size_t thermalvalue_avg_index; int* ofdm_index; int cck_index; int done_txpower; int* swing_idx_ofdm; int swing_idx_cck; scalar_t__ swing_idx_ofdm_cur; int swing_flag_ofdm; int swing_idx_cck_cur; int swing_flag_cck; scalar_t__ txpowercount; scalar_t__ txpower_track_control; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int AVG_THERMAL_NUM_88E ; 
 int /*<<< orphan*/  CAL_SWING_OFF (int,int,int /*<<< orphan*/ ,int) ; 
 int CCK_TABLE_LENGTH ; 
 int CCK_TABLE_SIZE ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  INDEX_MAPPING_NUM ; 
 long MASKCCK ; 
 int /*<<< orphan*/  MASKDWORD ; 
 long MASKOFDM_D ; 
 int OFDM_TABLE_LENGTH ; 
 int OFDM_TABLE_SIZE ; 
 int /*<<< orphan*/  RCCK0_TXFILTER2 ; 
 size_t RF90_PATH_A ; 
 int /*<<< orphan*/  RF_T_METER ; 
 int /*<<< orphan*/  ROFDM0_XATXIQIMBALANCE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TXAGC ; 
 int /*<<< orphan*/ ** cck_tbl_ch14 ; 
 int /*<<< orphan*/ ** cck_tbl_ch1_13 ; 
 int /*<<< orphan*/  dm_tx_pwr_track_set_pwr (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (long*,int /*<<< orphan*/ *,int) ; 
 long* ofdmswing_table ; 
 int /*<<< orphan*/  rtl88e_phy_iq_calibrate (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl88e_phy_lc_calibrate (struct ieee80211_hw*) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 long rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl_get_rfreg (struct ieee80211_hw*,size_t,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void dm_txpower_track_cb_therm(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 thermalvalue = 0, delta, delta_lck, delta_iqk, offset;
	u8 thermalvalue_avg_count = 0;
	u32 thermalvalue_avg = 0;
	long  ele_d, temp_cck;
	s8 ofdm_index[2], cck_index = 0,
		ofdm_index_old[2] = {0, 0}, cck_index_old = 0;
	int i = 0;
	/*bool is2t = false;*/

	u8 ofdm_min_index = 6, rf = 1;
	/*u8 index_for_channel;*/
	enum _power_dec_inc {power_dec, power_inc};

	/*0.1 the following TWO tables decide the
	 *final index of OFDM/CCK swing table
	 */
	s8 delta_swing_table_idx[2][15]  = {
		{0, 0, 2, 3, 4, 4, 5, 6, 7, 7, 8, 9, 10, 10, 11},
		{0, 0, -1, -2, -3, -4, -4, -4, -4, -5, -7, -8, -9, -9, -10}
	};
	u8 thermal_threshold[2][15] = {
		{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 27},
		{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 25, 25, 25}
	};

	/*Initilization (7 steps in total) */
	rtlpriv->dm.txpower_trackinginit = true;
	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "dm_txpower_track_cb_therm\n");

	thermalvalue = (u8)rtl_get_rfreg(hw, RF90_PATH_A, RF_T_METER,
					 0xfc00);
	if (!thermalvalue)
		return;
	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "Readback Thermal Meter = 0x%x pre thermal meter 0x%x eeprom_thermalmeter 0x%x\n",
		 thermalvalue, rtlpriv->dm.thermalvalue,
		 rtlefuse->eeprom_thermalmeter);

	/*1. Query OFDM Default Setting: Path A*/
	ele_d = rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE, MASKDWORD) &
			      MASKOFDM_D;
	for (i = 0; i < OFDM_TABLE_LENGTH; i++) {
		if (ele_d == (ofdmswing_table[i] & MASKOFDM_D)) {
			ofdm_index_old[0] = (u8)i;
			rtldm->swing_idx_ofdm_base[RF90_PATH_A] = (u8)i;
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Initial pathA ele_d reg0x%x = 0x%lx, ofdm_index = 0x%x\n",
				 ROFDM0_XATXIQIMBALANCE,
				 ele_d, ofdm_index_old[0]);
			break;
		}
	}

	/*2.Query CCK default setting From 0xa24*/
	temp_cck = rtl_get_bbreg(hw, RCCK0_TXFILTER2, MASKDWORD) & MASKCCK;
	for (i = 0; i < CCK_TABLE_LENGTH; i++) {
		if (rtlpriv->dm.cck_inch14) {
			if (memcmp(&temp_cck, &cck_tbl_ch14[i][2], 4) == 0) {
				cck_index_old = (u8)i;
				rtldm->swing_idx_cck_base = (u8)i;
				RT_TRACE(rtlpriv, COMP_POWER_TRACKING,
					 DBG_LOUD,
					 "Initial reg0x%x = 0x%lx, cck_index = 0x%x, ch 14 %d\n",
					 RCCK0_TXFILTER2, temp_cck,
					 cck_index_old,
					 rtlpriv->dm.cck_inch14);
				break;
			}
		} else {
			if (memcmp(&temp_cck, &cck_tbl_ch1_13[i][2], 4) == 0) {
				cck_index_old = (u8)i;
				rtldm->swing_idx_cck_base = (u8)i;
				RT_TRACE(rtlpriv, COMP_POWER_TRACKING,
					 DBG_LOUD,
					 "Initial reg0x%x = 0x%lx, cck_index = 0x%x, ch14 %d\n",
					 RCCK0_TXFILTER2, temp_cck,
					 cck_index_old,
					 rtlpriv->dm.cck_inch14);
				break;
			}
		}
	}

	/*3 Initialize ThermalValues of RFCalibrateInfo*/
	if (!rtldm->thermalvalue) {
		rtlpriv->dm.thermalvalue = rtlefuse->eeprom_thermalmeter;
		rtlpriv->dm.thermalvalue_lck = thermalvalue;
		rtlpriv->dm.thermalvalue_iqk = thermalvalue;
		for (i = 0; i < rf; i++)
			rtlpriv->dm.ofdm_index[i] = ofdm_index_old[i];
		rtlpriv->dm.cck_index = cck_index_old;
	}

	/*4 Calculate average thermal meter*/
	rtldm->thermalvalue_avg[rtldm->thermalvalue_avg_index] = thermalvalue;
	rtldm->thermalvalue_avg_index++;
	if (rtldm->thermalvalue_avg_index == AVG_THERMAL_NUM_88E)
		rtldm->thermalvalue_avg_index = 0;

	for (i = 0; i < AVG_THERMAL_NUM_88E; i++) {
		if (rtldm->thermalvalue_avg[i]) {
			thermalvalue_avg += rtldm->thermalvalue_avg[i];
			thermalvalue_avg_count++;
		}
	}

	if (thermalvalue_avg_count)
		thermalvalue = (u8)(thermalvalue_avg / thermalvalue_avg_count);

	/* 5 Calculate delta, delta_LCK, delta_IQK.*/
	if (rtlhal->reloadtxpowerindex) {
		delta = (thermalvalue > rtlefuse->eeprom_thermalmeter) ?
		    (thermalvalue - rtlefuse->eeprom_thermalmeter) :
		    (rtlefuse->eeprom_thermalmeter - thermalvalue);
		rtlhal->reloadtxpowerindex = false;
		rtlpriv->dm.done_txpower = false;
	} else if (rtlpriv->dm.done_txpower) {
		delta = (thermalvalue > rtlpriv->dm.thermalvalue) ?
		    (thermalvalue - rtlpriv->dm.thermalvalue) :
		    (rtlpriv->dm.thermalvalue - thermalvalue);
	} else {
		delta = (thermalvalue > rtlefuse->eeprom_thermalmeter) ?
		    (thermalvalue - rtlefuse->eeprom_thermalmeter) :
		    (rtlefuse->eeprom_thermalmeter - thermalvalue);
	}
	delta_lck = (thermalvalue > rtlpriv->dm.thermalvalue_lck) ?
	    (thermalvalue - rtlpriv->dm.thermalvalue_lck) :
	    (rtlpriv->dm.thermalvalue_lck - thermalvalue);
	delta_iqk = (thermalvalue > rtlpriv->dm.thermalvalue_iqk) ?
	    (thermalvalue - rtlpriv->dm.thermalvalue_iqk) :
	    (rtlpriv->dm.thermalvalue_iqk - thermalvalue);

	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "Readback Thermal Meter = 0x%x pre thermal meter 0x%x eeprom_thermalmeter 0x%x delta 0x%x delta_lck 0x%x delta_iqk 0x%x\n",
		 thermalvalue, rtlpriv->dm.thermalvalue,
		 rtlefuse->eeprom_thermalmeter, delta, delta_lck,
		 delta_iqk);
	/* 6 If necessary, do LCK.*/
	if (delta_lck >= 8) {
		rtlpriv->dm.thermalvalue_lck = thermalvalue;
		rtl88e_phy_lc_calibrate(hw);
	}

	/* 7 If necessary, move the index of
	 * swing table to adjust Tx power.
	 */
	if (delta > 0 && rtlpriv->dm.txpower_track_control) {
		delta = (thermalvalue > rtlefuse->eeprom_thermalmeter) ?
		    (thermalvalue - rtlefuse->eeprom_thermalmeter) :
		    (rtlefuse->eeprom_thermalmeter - thermalvalue);

		/* 7.1 Get the final CCK_index and OFDM_index for each
		 * swing table.
		 */
		if (thermalvalue > rtlefuse->eeprom_thermalmeter) {
			CAL_SWING_OFF(offset, power_inc, INDEX_MAPPING_NUM,
				      delta);
			for (i = 0; i < rf; i++)
				ofdm_index[i] =
				  rtldm->ofdm_index[i] +
				  delta_swing_table_idx[power_inc][offset];
			cck_index = rtldm->cck_index +
				delta_swing_table_idx[power_inc][offset];
		} else {
			CAL_SWING_OFF(offset, power_dec, INDEX_MAPPING_NUM,
				      delta);
			for (i = 0; i < rf; i++)
				ofdm_index[i] =
				  rtldm->ofdm_index[i] +
				  delta_swing_table_idx[power_dec][offset];
			cck_index = rtldm->cck_index +
				delta_swing_table_idx[power_dec][offset];
		}

		/* 7.2 Handle boundary conditions of index.*/
		for (i = 0; i < rf; i++) {
			if (ofdm_index[i] > OFDM_TABLE_SIZE-1)
				ofdm_index[i] = OFDM_TABLE_SIZE-1;
			else if (rtldm->ofdm_index[i] < ofdm_min_index)
				ofdm_index[i] = ofdm_min_index;
		}

		if (cck_index > CCK_TABLE_SIZE-1)
			cck_index = CCK_TABLE_SIZE-1;
		else if (cck_index < 0)
			cck_index = 0;

		/*7.3Configure the Swing Table to adjust Tx Power.*/
		if (rtlpriv->dm.txpower_track_control) {
			rtldm->done_txpower = true;
			rtldm->swing_idx_ofdm[RF90_PATH_A] =
				(u8)ofdm_index[RF90_PATH_A];
			rtldm->swing_idx_cck = cck_index;
			if (rtldm->swing_idx_ofdm_cur !=
			    rtldm->swing_idx_ofdm[0]) {
				rtldm->swing_idx_ofdm_cur =
					 rtldm->swing_idx_ofdm[0];
				rtldm->swing_flag_ofdm = true;
			}

			if (rtldm->swing_idx_cck_cur != rtldm->swing_idx_cck) {
				rtldm->swing_idx_cck_cur = rtldm->swing_idx_cck;
				rtldm->swing_flag_cck = true;
			}

			dm_tx_pwr_track_set_pwr(hw, TXAGC, 0, 0);
		}
	}

	if (delta_iqk >= 8) {
		rtlpriv->dm.thermalvalue_iqk = thermalvalue;
		rtl88e_phy_iq_calibrate(hw, false);
	}

	if (rtldm->txpower_track_control)
		rtldm->thermalvalue = thermalvalue;
	rtldm->txpowercount = 0;
	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD, "end\n");
}