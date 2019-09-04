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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {int cur_dac_swing_on; int pre_dac_swing_on; int /*<<< orphan*/  cur_dac_swing_lvl; int /*<<< orphan*/  pre_dac_swing_lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  btc8723b2ant_set_sw_fulltime_dac_swing (struct btc_coexist*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void btc8723b2ant_dac_swing(struct btc_coexist *btcoexist,
				   bool force_exec, bool dac_swing_on,
				   u32 dac_swing_lvl)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s turn DacSwing=%s, dac_swing_lvl=0x%x\n",
		 (force_exec ? "force to" : ""),
		 (dac_swing_on ? "ON" : "OFF"), dac_swing_lvl);
	coex_dm->cur_dac_swing_on = dac_swing_on;
	coex_dm->cur_dac_swing_lvl = dac_swing_lvl;

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], bPreDacSwingOn=%d, preDacSwingLvl=0x%x, bCurDacSwingOn=%d, curDacSwingLvl=0x%x\n",
			 coex_dm->pre_dac_swing_on,
			 coex_dm->pre_dac_swing_lvl,
			 coex_dm->cur_dac_swing_on,
			 coex_dm->cur_dac_swing_lvl);

		if ((coex_dm->pre_dac_swing_on == coex_dm->cur_dac_swing_on) &&
		    (coex_dm->pre_dac_swing_lvl == coex_dm->cur_dac_swing_lvl))
			return;
	}
	mdelay(30);
	btc8723b2ant_set_sw_fulltime_dac_swing(btcoexist, dac_swing_on,
					       dac_swing_lvl);

	coex_dm->pre_dac_swing_on = coex_dm->cur_dac_swing_on;
	coex_dm->pre_dac_swing_lvl = coex_dm->cur_dac_swing_lvl;
}