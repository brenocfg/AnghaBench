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
 int /*<<< orphan*/  BIT0 ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
halbtc8723b1ant_set_fw_ignore_wlan_act(struct btc_coexist *btcoexist,
				       bool enable)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = {0};

	if (enable)
		h2c_parameter[0] |= BIT0;	/* function enable */

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], set FW for BT Ignore Wlan_Act, FW write 0x63 = 0x%x\n",
		 h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x63, 1, h2c_parameter);
}