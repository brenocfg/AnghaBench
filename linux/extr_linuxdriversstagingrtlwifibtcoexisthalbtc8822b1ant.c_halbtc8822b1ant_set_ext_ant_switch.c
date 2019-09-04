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
struct btc_coexist {int (* btc_read_4byte ) (struct btc_coexist*,int) ;int /*<<< orphan*/  (* btc_write_1byte_bitmask ) (struct btc_coexist*,int,int,int) ;int /*<<< orphan*/  (* btc_write_1byte ) (struct btc_coexist*,int,int) ;struct rtl_priv* adapter; } ;
struct TYPE_4__ {int cur_ext_ant_switch_status; scalar_t__ pre_ext_ant_switch_status; } ;
struct TYPE_3__ {int ext_ant_switch_ctrl_polarity; scalar_t__ ext_ant_switch_type; int /*<<< orphan*/  ext_ant_switch_exist; } ;

/* Variables and functions */
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_ANTDIV 136 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_BBSW 135 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_BT 134 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_MAC 133 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_PTA 132 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_TO_BT 131 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_TO_NOCARE 130 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_TO_WLA 129 
#define  BT_8822B_1ANT_EXT_ANT_SWITCH_TO_WLG 128 
 scalar_t__ BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 TYPE_2__* coex_dm ; 
 TYPE_1__* rfe_type ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub10 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub11 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub12 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub13 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub14 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub15 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub16 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub17 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub18 (struct btc_coexist*,int,int,int) ; 
 int stub19 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int,int) ; 
 int stub20 (struct btc_coexist*,int) ; 
 int stub21 (struct btc_coexist*,int) ; 
 int /*<<< orphan*/  stub3 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub5 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub6 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub7 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct btc_coexist*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct btc_coexist*,int,int,int) ; 

__attribute__((used)) static void halbtc8822b1ant_set_ext_ant_switch(struct btc_coexist *btcoexist,
					       bool force_exec, u8 ctrl_type,
					       u8 pos_type)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	bool switch_polatiry_inverse = false;
	u8 regval_0xcbd = 0, regval_0x64;
	u32 u32tmp1 = 0, u32tmp2 = 0, u32tmp3 = 0;

	/* Ext switch buffer mux */
	btcoexist->btc_write_1byte(btcoexist, 0x974, 0xff);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0x1991, 0x3, 0x0);
	btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbe, 0x8, 0x0);

	if (!rfe_type->ext_ant_switch_exist)
		return;

	coex_dm->cur_ext_ant_switch_status = (ctrl_type << 8) + pos_type;

	if (!force_exec) {
		if (coex_dm->pre_ext_ant_switch_status ==
		    coex_dm->cur_ext_ant_switch_status)
			return;
	}

	coex_dm->pre_ext_ant_switch_status = coex_dm->cur_ext_ant_switch_status;

	/* swap control polarity if use different switch control polarity*/
	/* Normal switch polarity for SPDT,
	 * 0xcbd[1:0] = 2b'01 => Ant to BTG,
	 * 0xcbd[1:0] = 2b'10 => Ant to WLG
	 */
	switch_polatiry_inverse = rfe_type->ext_ant_switch_ctrl_polarity == 1;

	switch (pos_type) {
	default:
	case BT_8822B_1ANT_EXT_ANT_SWITCH_TO_BT:
	case BT_8822B_1ANT_EXT_ANT_SWITCH_TO_NOCARE:

		break;
	case BT_8822B_1ANT_EXT_ANT_SWITCH_TO_WLG:
		break;
	case BT_8822B_1ANT_EXT_ANT_SWITCH_TO_WLA:
		break;
	}

	if (rfe_type->ext_ant_switch_type ==
	    BT_8822B_1ANT_EXT_ANT_SWITCH_USE_SPDT) {
		switch (ctrl_type) {
		default:
		case BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_BBSW:
			/*  0x4c[23] = 0 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e,
							   0x80, 0x0);
			/* 0x4c[24] = 1 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f,
							   0x01, 0x1);
			/* BB SW, DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin*/
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb4,
							   0xff, 0x77);

			/* 0xcbd[1:0] = 2b'01 for no switch_polatiry_inverse,
			 * ANTSWB =1, ANTSW =0
			 */
			regval_0xcbd = (!switch_polatiry_inverse ? 0x1 : 0x2);
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd,
							   0x3, regval_0xcbd);

			break;
		case BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_PTA:
			/* 0x4c[23] = 0 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e,
							   0x80, 0x0);
			/* 0x4c[24] = 1 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f,
							   0x01, 0x1);
			/* PTA,  DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb4,
							   0xff, 0x66);

			/* 0xcbd[1:0] = 2b'10 for no switch_polatiry_inverse,
			 * ANTSWB =1, ANTSW =0  @ GNT_BT=1
			 */
			regval_0xcbd = (!switch_polatiry_inverse ? 0x2 : 0x1);
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcbd,
							   0x3, regval_0xcbd);

			break;
		case BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_ANTDIV:
			/* 0x4c[23] = 0 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e,
							   0x80, 0x0);
			/* 0x4c[24] = 1 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f,
							   0x01, 0x1);
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0xcb4,
							   0xff, 0x88);

			/* no regval_0xcbd setup required, because
			 * antenna switch control value by antenna diversity
			 */

			break;
		case BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_MAC:
			/*  0x4c[23] = 1 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e,
							   0x80, 0x1);

			/* 0x64[0] = 1b'0 for no switch_polatiry_inverse,
			 * DPDT_SEL_N =1, DPDT_SEL_P =0
			 */
			regval_0x64 = (!switch_polatiry_inverse ? 0x0 : 0x1);
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x64, 0x1,
							   regval_0x64);
			break;
		case BT_8822B_1ANT_EXT_ANT_SWITCH_CTRL_BY_BT:
			/* 0x4c[23] = 0 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4e,
							   0x80, 0x0);
			/* 0x4c[24] = 0 */
			btcoexist->btc_write_1byte_bitmask(btcoexist, 0x4f,
							   0x01, 0x0);

			/* no setup required, because antenna switch control
			 * value by BT vendor 0xac[1:0]
			 */
			break;
		}
	}

	u32tmp1 = btcoexist->btc_read_4byte(btcoexist, 0xcbc);
	u32tmp2 = btcoexist->btc_read_4byte(btcoexist, 0x4c);
	u32tmp3 = btcoexist->btc_read_4byte(btcoexist, 0x64) & 0xff;

	RT_TRACE(
		rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], ********** (After Ext Ant switch setup) 0xcbc = 0x%08x, 0x4c = 0x%08x, 0x64= 0x%02x**********\n",
		u32tmp1, u32tmp2, u32tmp3);
}