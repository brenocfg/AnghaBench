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
struct rtl_priv {int dummy; } ;
struct btc_board_info {scalar_t__ btdm_ant_pos; } ;
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;int (* btc_read_1byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_4byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int*) ;int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;int /*<<< orphan*/  (* btc_get ) (struct btc_coexist*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* btc_set_rf_reg ) (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ;struct btc_board_info board_info; struct rtl_priv* adapter; } ;
struct TYPE_2__ {int cur_ant_pos_type; scalar_t__ pre_ant_pos_type; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int BIT23 ; 
 int BIT24 ; 
 scalar_t__ BTC_ANTENNA_AT_MAIN_PORT ; 
#define  BTC_ANT_PATH_BT 130 
#define  BTC_ANT_PATH_PTA 129 
#define  BTC_ANT_PATH_WIFI 128 
 int /*<<< orphan*/  BTC_GET_BL_EXT_SWITCH ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_IS_IN_MP_MODE ; 
 int /*<<< orphan*/  BTC_GET_U4_WIFI_FW_VER ; 
 int /*<<< orphan*/  BTC_RF_A ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub13 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub14 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub15 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub16 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub17 (struct btc_coexist*,int,int,int) ; 
 int stub18 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub19 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int /*<<< orphan*/ ,int*) ; 
 int stub20 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub21 (struct btc_coexist*,int,int,int*) ; 
 int stub22 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub23 (struct btc_coexist*,int,int) ; 
 int stub24 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub25 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub26 (struct btc_coexist*,int,int,int) ; 
 int stub27 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub28 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub29 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub30 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub31 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub32 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub33 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub34 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub35 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub36 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub37 (struct btc_coexist*,int,int,int) ; 
 int stub38 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub39 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub40 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub41 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub42 (struct btc_coexist*,int,int,int*) ; 
 int /*<<< orphan*/  stub43 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub44 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub45 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub46 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub47 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub48 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void halbtc8723b1ant_set_ant_path(struct btc_coexist *btcoexist,
					 u8 ant_pos_type, bool force_exec,
					 bool init_hw_cfg, bool wifi_off)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	struct btc_board_info *board_info = &btcoexist->board_info;
	u32 fw_ver = 0, u32tmp = 0, cnt_bt_cal_chk = 0;
	bool pg_ext_switch = false;
	bool use_ext_switch = false;
	bool is_in_mp_mode = false;
	u8 h2c_parameter[2] = {0}, u8tmp = 0;

	coex_dm->cur_ant_pos_type = ant_pos_type;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_EXT_SWITCH, &pg_ext_switch);
	/* [31:16] = fw ver, [15:0] = fw sub ver */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);

	if ((fw_ver < 0xc0000) || pg_ext_switch)
		use_ext_switch = true;

	if (init_hw_cfg) {
		/* WiFi TRx Mask on */
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x780);
		/* remove due to interrupt is disabled that polling c2h will
		 * fail and delay 100ms.
		 */

		if (fw_ver >= 0x180000) {
			/* Use H2C to set GNT_BT to HIGH */
			h2c_parameter[0] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		} else {
			/* set grant_bt to high */
			btcoexist->btc_write_1byte(btcoexist, 0x765, 0x18);
		}
		/* set wlan_act control by PTA */
		btcoexist->btc_write_1byte(btcoexist, 0x76e, 0x4);

		/* BT select s0/s1 is controlled by BT */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67, 0x20, 0x0);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x39, 0x8, 0x1);
		btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x944, 0x3, 0x3);
		btcoexist->btc_write_1byte(btcoexist, 0x930, 0x77);
	} else if (wifi_off) {
		if (fw_ver >= 0x180000) {
			/* Use H2C to set GNT_BT to HIGH */
			h2c_parameter[0] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		} else {
			/* set grant_bt to high */
			btcoexist->btc_write_1byte(btcoexist, 0x765, 0x18);
		}
		/* set wlan_act to always low */
		btcoexist->btc_write_1byte(btcoexist, 0x76e, 0x4);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE,
				   &is_in_mp_mode);
		if (!is_in_mp_mode)
			/* BT select s0/s1 is controlled by BT */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67,
							   0x20, 0x0);
		else
			/* BT select s0/s1 is controlled by WiFi */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x67,
							   0x20, 0x1);

		/* 0x4c[24:23]=00, Set Antenna control by BT_RFE_CTRL
		 * BT Vendor 0xac=0xf002
		 */
		u32tmp = btcoexist->btc_read_4byte(btcoexist, 0x4c);
		u32tmp &= ~BIT23;
		u32tmp &= ~BIT24;
		btcoexist->btc_write_4byte(btcoexist, 0x4c, u32tmp);
	} else {
		/* Use H2C to set GNT_BT to LOW */
		if (fw_ver >= 0x180000) {
			if (btcoexist->btc_read_1byte(btcoexist, 0x765) != 0) {
				h2c_parameter[0] = 0;
				btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
							h2c_parameter);
			}
		} else {
			/* BT calibration check */
			while (cnt_bt_cal_chk <= 20) {
				u8tmp = btcoexist->btc_read_1byte(btcoexist,
								  0x49d);
				cnt_bt_cal_chk++;
				if (u8tmp & BIT(0)) {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], ########### BT is calibrating (wait cnt=%d) ###########\n",
						 cnt_bt_cal_chk);
					mdelay(50);
				} else {
					RT_TRACE(rtlpriv, COMP_BT_COEXIST,
						 DBG_LOUD,
						 "[BTCoex], ********** BT is NOT calibrating (wait cnt=%d)**********\n",
						 cnt_bt_cal_chk);
					break;
				}
			}

			/* set grant_bt to PTA */
			btcoexist->btc_write_1byte(btcoexist, 0x765, 0x0);
		}

		if (btcoexist->btc_read_1byte(btcoexist, 0x76e) != 0xc) {
			/* set wlan_act control by PTA */
			btcoexist->btc_write_1byte(btcoexist, 0x76e, 0xc);
		}

		btcoexist->btc_write_1byte_bitmask(
			btcoexist, 0x67, 0x20,
			0x1); /* BT select s0/s1 is controlled by WiFi */
	}

	if (use_ext_switch) {
		if (init_hw_cfg) {
			/* 0x4c[23] = 0, 0x4c[24] = 1
			 * Antenna control by WL/BT
			 */
			u32tmp = btcoexist->btc_read_4byte(btcoexist, 0x4c);
			u32tmp &= ~BIT23;
			u32tmp |= BIT24;
			btcoexist->btc_write_4byte(btcoexist, 0x4c, u32tmp);

			/* fixed internal switch S1->WiFi, S0->BT */
			btcoexist->btc_write_4byte(btcoexist, 0x948, 0x0);

			if (board_info->btdm_ant_pos ==
			    BTC_ANTENNA_AT_MAIN_PORT) {
				/* tell firmware "no antenna inverse" */
				h2c_parameter[0] = 0;
				/* ext switch type */
				h2c_parameter[1] = 1;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			} else {
				/* tell firmware "antenna inverse" */
				h2c_parameter[0] = 1;
				/* ext switch type */
				h2c_parameter[1] = 1;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			}
		}

		if (force_exec ||
		    (coex_dm->cur_ant_pos_type != coex_dm->pre_ant_pos_type)) {
			/* ext switch setting */
			switch (ant_pos_type) {
			case BTC_ANT_PATH_WIFI:
				if (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_write_1byte_bitmask(
						btcoexist, 0x92c, 0x3, 0x1);
				else
					btcoexist->btc_write_1byte_bitmask(
						btcoexist, 0x92c, 0x3, 0x2);
				break;
			case BTC_ANT_PATH_BT:
				if (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_write_1byte_bitmask(
						btcoexist, 0x92c, 0x3, 0x2);
				else
					btcoexist->btc_write_1byte_bitmask(
						btcoexist, 0x92c, 0x3, 0x1);
				break;
			default:
			case BTC_ANT_PATH_PTA:
				if (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_write_1byte_bitmask(
						btcoexist, 0x92c, 0x3, 0x1);
				else
					btcoexist->btc_write_1byte_bitmask(
						btcoexist, 0x92c, 0x3, 0x2);
				break;
			}
		}
	} else {
		if (init_hw_cfg) {
			/* 0x4c[23] = 1, 0x4c[24] = 0,
			 * Antenna control by 0x64
			 */
			u32tmp = btcoexist->btc_read_4byte(btcoexist, 0x4c);
			u32tmp |= BIT23;
			u32tmp &= ~BIT24;
			btcoexist->btc_write_4byte(btcoexist, 0x4c, u32tmp);

			/* Fix Ext switch Main->S1, Aux->S0 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x64, 0x1,
							   0x0);

			if (board_info->btdm_ant_pos ==
			    BTC_ANTENNA_AT_MAIN_PORT) {
				/* tell firmware "no antenna inverse" */
				h2c_parameter[0] = 0;
				/* internal switch type */
				h2c_parameter[1] = 0;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			} else {
				/* tell firmware "antenna inverse" */
				h2c_parameter[0] = 1;
				/* internal switch type */
				h2c_parameter[1] = 0;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			}
		}

		if (force_exec ||
		    (coex_dm->cur_ant_pos_type != coex_dm->pre_ant_pos_type)) {
			/* internal switch setting */
			switch (ant_pos_type) {
			case BTC_ANT_PATH_WIFI:
				if (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_write_4byte(btcoexist,
							0x948, 0x0);
				else
					btcoexist->btc_write_4byte(btcoexist,
							0x948, 0x280);
				break;
			case BTC_ANT_PATH_BT:
				if (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_write_4byte(btcoexist,
							0x948, 0x280);
				else
					btcoexist->btc_write_4byte(btcoexist,
							0x948, 0x0);
				break;
			default:
			case BTC_ANT_PATH_PTA:
				if (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_write_4byte(btcoexist,
							0x948, 0x200);
				else
					btcoexist->btc_write_4byte(btcoexist,
							0x948, 0x80);
				break;
			}
		}
	}

	coex_dm->pre_ant_pos_type = coex_dm->cur_ant_pos_type;
}