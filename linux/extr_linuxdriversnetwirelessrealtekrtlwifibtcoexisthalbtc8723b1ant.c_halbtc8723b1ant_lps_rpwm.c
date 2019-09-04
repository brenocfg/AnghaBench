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
typedef  void* u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {void* cur_rpwm; void* pre_rpwm; void* cur_lps; void* pre_lps; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,void*,...) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  halbtc8723b1ant_set_lps_rpwm (struct btc_coexist*,void*,void*) ; 

__attribute__((used)) static void halbtc8723b1ant_lps_rpwm(struct btc_coexist *btcoexist,
				     bool force_exec,
				     u8 lps_val, u8 rpwm_val)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s set lps/rpwm = 0x%x/0x%x\n",
		 (force_exec ? "force to" : ""), lps_val, rpwm_val);
	coex_dm->cur_lps = lps_val;
	coex_dm->cur_rpwm = rpwm_val;

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], LPS-RxBeaconMode = 0x%x , LPS-RPWM = 0x%x!!\n",
			 coex_dm->cur_lps, coex_dm->cur_rpwm);

		if ((coex_dm->pre_lps == coex_dm->cur_lps) &&
		    (coex_dm->pre_rpwm == coex_dm->cur_rpwm)) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				 "[BTCoex], LPS-RPWM_Last = 0x%x , LPS-RPWM_Now = 0x%x!!\n",
				 coex_dm->pre_rpwm, coex_dm->cur_rpwm);

			return;
		}
	}
	halbtc8723b1ant_set_lps_rpwm(btcoexist, lps_val, rpwm_val);

	coex_dm->pre_lps = coex_dm->cur_lps;
	coex_dm->pre_rpwm = coex_dm->cur_rpwm;
}