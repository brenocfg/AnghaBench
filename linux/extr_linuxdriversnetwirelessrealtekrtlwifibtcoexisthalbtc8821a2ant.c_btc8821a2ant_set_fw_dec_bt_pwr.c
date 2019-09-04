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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int /*<<< orphan*/  (* btc_fill_h2c ) (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ;struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btc8821a2ant_set_fw_dec_bt_pwr(struct btc_coexist *btcoexist,
					   u8 dec_bt_pwr_lvl)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = {0};

	h2c_parameter[0] = dec_bt_pwr_lvl;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], decrease Bt Power Level : %u, FW write 0x62 = 0x%x\n",
		 dec_bt_pwr_lvl, h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x62, 1, h2c_parameter);
}