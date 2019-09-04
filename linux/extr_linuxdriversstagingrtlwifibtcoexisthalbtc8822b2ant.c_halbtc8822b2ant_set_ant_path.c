#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int (* btc_read_1byte ) (struct btc_coexist*,int) ;int (* btc_read_4byte ) (struct btc_coexist*,int) ;scalar_t__ dbg_mode_2ant; int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;struct rtl_priv* adapter; } ;
struct TYPE_4__ {int cur_ant_pos_type; scalar_t__ pre_ant_pos_type; } ;
struct TYPE_3__ {int run_time_state; int /*<<< orphan*/  gnt_error_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_8822B_2ANT_CTT_BT_VS_LTE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_CTT_WL_VS_LTE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_BT ; 
 int /*<<< orphan*/  BT_8822B_2ANT_EXT_ANT_SWITCH_MAIN_TO_NOCARE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_GNT_BLOCK_RFC_BB ; 
 int /*<<< orphan*/  BT_8822B_2ANT_GNT_TYPE_CTRL_BY_PTA ; 
 int /*<<< orphan*/  BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PCO_BTSIDE ; 
 int /*<<< orphan*/  BT_8822B_2ANT_PCO_WLSIDE ; 
#define  BT_8822B_2ANT_PHASE_2G_RUNTIME 135 
#define  BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT 134 
#define  BT_8822B_2ANT_PHASE_5G_RUNTIME 133 
#define  BT_8822B_2ANT_PHASE_BTMPMODE 132 
#define  BT_8822B_2ANT_PHASE_COEX_INIT 131 
#define  BT_8822B_2ANT_PHASE_COEX_POWERON 130 
#define  BT_8822B_2ANT_PHASE_WLANONLY_INIT 129 
#define  BT_8822B_2ANT_PHASE_WLAN_OFF 128 
 int /*<<< orphan*/  BT_8822B_2ANT_SIG_STA_SET_BY_HW ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SIG_STA_SET_TO_HIGH ; 
 int /*<<< orphan*/  BT_8822B_2ANT_SIG_STA_SET_TO_LOW ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* coex_sta ; 
 int /*<<< orphan*/  halbtc8822b2ant_ltecoex_enable (struct btc_coexist*,int) ; 
 int halbtc8822b2ant_ltecoex_indirect_read_reg (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ltecoex_pathcontrol_owner (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ltecoex_set_coex_table (struct btc_coexist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ltecoex_set_gnt_bt (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_ltecoex_set_gnt_wl (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8822b2ant_set_ext_ant_switch (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub13 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub14 (struct btc_coexist*,int,int,int) ; 
 int stub15 (struct btc_coexist*,int) ; 
 int stub16 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int,int) ; 
 int stub6 (struct btc_coexist*,int) ; 
 int stub7 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b2ant_set_ant_path(struct btc_coexist *btcoexist,
					 u8 ant_pos_type, bool force_exec,
					 u8 phase)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 u8tmp = 0;
	u32 u32tmp1 = 0;
	u32 u32tmp2 = 0, u32tmp3 = 0;

	u32tmp1 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist, 0x38);

	/* To avoid indirect access fail  */
	if (((u32tmp1 & 0xf000) >> 12) != ((u32tmp1 & 0x0f00) >> 8)) {
		force_exec = true;
		coex_sta->gnt_error_cnt++;
	}

	/* Ext switch buffer mux */
	btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x1991, 0x3, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbe, 0x8, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
					   0x0); /*  0x4c[23] = 0 */
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
					   0x1); /* 0x4c[24] = 1 */

	coex_dm->cur_ant_pos_type = (ant_pos_type << 8) + phase;

	if (!force_exec) {
		if (coex_dm->cur_ant_pos_type == coex_dm->pre_ant_pos_type)
			return;
	}

	coex_dm->pre_ant_pos_type = coex_dm->cur_ant_pos_type;

	if (btcoexist->dbg_mode_2ant) {
		u32tmp1 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								    0x38);
		u32tmp2 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								    0x54);
		u8tmp = btcoexist->btc_read_1byte(btcoexist, 0x73);

		u32tmp3 = btcoexist->btc_read_4byte(btcoexist, 0xcb4);

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], (Before Ant Setup) 0xcb4 = 0x%x, 0x73 = 0x%x, 0x38= 0x%x, 0x54= 0x%x\n",
			u32tmp3, u8tmp, u32tmp1, u32tmp2);
	}

	switch (phase) {
	case BT_8822B_2ANT_PHASE_COEX_POWERON:

		/* set Path control owner to WL at initial step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_BTSIDE);

		/* set GNT_BT to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		/* Set GNT_WL to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		coex_sta->run_time_state = false;

		break;
	case BT_8822B_2ANT_PHASE_COEX_INIT:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /*  0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x1); /* 0x4c[24] = 1 */
		/* Disable LTE Coex Function in WiFi side
		 * (this should be on if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* GNT_WL_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_WL_VS_LTE, 0xffff);

		/* GNT_BT_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_BT_VS_LTE, 0xffff);

		/* set Path control owner to WL at initial step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		/* Set GNT_WL to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		coex_sta->run_time_state = false;

		break;
	case BT_8822B_2ANT_PHASE_WLANONLY_INIT:
		/* Disable LTE Coex Function in WiFi side
		 * (this should be on if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* GNT_WL_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_WL_VS_LTE, 0xffff);

		/* GNT_BT_LTE always = 1
		 * (this should be config if LTE coex is required)
		 */
		halbtc8822b2ant_ltecoex_set_coex_table(
			btcoexist, BT_8822B_2ANT_CTT_BT_VS_LTE, 0xffff);

		/* set Path control owner to WL at initial step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW Low */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_LOW);
		/* Set GNT_WL to SW high */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		coex_sta->run_time_state = false;

		break;
	case BT_8822B_2ANT_PHASE_WLAN_OFF:
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e, 0x80,
						   0x0); /* 0x4c[23] = 0 */
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f, 0x01,
						   0x0); /* 0x4c[24] = 0 */
		/* Disable LTE Coex Function in WiFi side */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* set Path control owner to BT */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_BTSIDE);

		/* Set Ext Ant Switch to BT control at wifi off step */
		halbtc8822b2ant_set_ext_ant_switch(
			btcoexist, FORCE_EXEC,
			BT_8822B_2ANT_EXT_ANT_SWITCH_CTRL_BY_BT,
			BT_8822B_2ANT_EXT_ANT_SWITCH_MAIN_TO_NOCARE);
		coex_sta->run_time_state = false;
		break;
	case BT_8822B_2ANT_PHASE_2G_RUNTIME:
	case BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT:

		/* set Path control owner to WL at runtime step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);
		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb4, 0xff,
						   0x66);
		if (phase == BT_8822B_2ANT_PHASE_2G_RUNTIME_CONCURRENT) {
			/* set GNT_BT to PTA */
			halbtc8822b2ant_ltecoex_set_gnt_bt(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_PTA,
				BT_8822B_2ANT_SIG_STA_SET_BY_HW);

			/* Set GNT_WL to SW High */
			halbtc8822b2ant_ltecoex_set_gnt_wl(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
				BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		} else {
			/* set GNT_BT to PTA */
			halbtc8822b2ant_ltecoex_set_gnt_bt(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_PTA,
				BT_8822B_2ANT_SIG_STA_SET_BY_HW);

			/* Set GNT_WL to PTA */
			halbtc8822b2ant_ltecoex_set_gnt_wl(
				btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
				BT_8822B_2ANT_GNT_TYPE_CTRL_BY_PTA,
				BT_8822B_2ANT_SIG_STA_SET_BY_HW);
		}

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ************* under2g 0xcbd setting =2 *************\n");

		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd, 0x03, 02);
		break;

	case BT_8822B_2ANT_PHASE_5G_RUNTIME:

		/* set Path control owner to WL at runtime step */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW Hi */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		/* Set GNT_WL to SW Hi */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);
		coex_sta->run_time_state = true;

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ************* under5g 0xcbd setting =1 *************\n");

		btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd, 0x03, 01);

		break;
	case BT_8822B_2ANT_PHASE_BTMPMODE:
		/* Disable LTE Coex Function in WiFi side */
		halbtc8822b2ant_ltecoex_enable(btcoexist, 0x0);

		/* set Path control owner to WL */
		halbtc8822b2ant_ltecoex_pathcontrol_owner(
			btcoexist, BT_8822B_2ANT_PCO_WLSIDE);

		/* set GNT_BT to SW Hi */
		halbtc8822b2ant_ltecoex_set_gnt_bt(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_HIGH);

		/* Set GNT_WL to SW Lo */
		halbtc8822b2ant_ltecoex_set_gnt_wl(
			btcoexist, BT_8822B_2ANT_GNT_BLOCK_RFC_BB,
			BT_8822B_2ANT_GNT_TYPE_CTRL_BY_SW,
			BT_8822B_2ANT_SIG_STA_SET_TO_LOW);

		coex_sta->run_time_state = false;
		break;
	}

	if (btcoexist->dbg_mode_2ant) {
		u32tmp1 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								    0x38);
		u32tmp2 = halbtc8822b2ant_ltecoex_indirect_read_reg(btcoexist,
								    0x54);
		u32tmp3 = btcoexist->btc_read_4byte(btcoexist, 0xcb4);
		u8tmp = btcoexist->btc_read_1byte(btcoexist, 0x73);

		RT_TRACE(
			rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], (After Ant-Setup phase---%d) 0xcb4 = 0x%x, 0x73 = 0x%x, 0x38= 0x%x, 0x54= 0x%x\n",
			phase, u32tmp3, u8tmp, u32tmp1, u32tmp2);
	}
}