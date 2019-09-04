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
typedef  scalar_t__ u8 ;
typedef  void* u32 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_2__ {scalar_t__ cur_val0x6c4; scalar_t__ cur_val0x6c8; scalar_t__ cur_val0x6cc; scalar_t__ pre_val0x6c4; scalar_t__ pre_val0x6c8; scalar_t__ pre_val0x6cc; void* cur_val0x6c0; void* pre_val0x6c0; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  btc8723b2ant_set_coex_table (struct btc_coexist*,void*,void*,void*,scalar_t__) ; 
 TYPE_1__* coex_dm ; 

__attribute__((used)) static void btc8723b2ant_coex_table(struct btc_coexist *btcoexist,
				    bool force_exec, u32 val0x6c0,
				    u32 val0x6c4, u32 val0x6c8,
				    u8 val0x6cc)
{
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "[BTCoex], %s write Coex Table 0x6c0=0x%x, 0x6c4=0x%x, 0x6c8=0x%x, 0x6cc=0x%x\n",
		 force_exec ? "force to" : "",
		 val0x6c0, val0x6c4, val0x6c8, val0x6cc);
	coex_dm->cur_val0x6c0 = val0x6c0;
	coex_dm->cur_val0x6c4 = val0x6c4;
	coex_dm->cur_val0x6c8 = val0x6c8;
	coex_dm->cur_val0x6cc = val0x6cc;

	if (!force_exec) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], preVal0x6c0=0x%x, preVal0x6c4=0x%x, preVal0x6c8=0x%x, preVal0x6cc=0x%x !!\n",
			 coex_dm->pre_val0x6c0, coex_dm->pre_val0x6c4,
			 coex_dm->pre_val0x6c8, coex_dm->pre_val0x6cc);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			 "[BTCoex], curVal0x6c0=0x%x, curVal0x6c4=0x%x, curVal0x6c8=0x%x, curVal0x6cc=0x%x !!\n",
			 coex_dm->cur_val0x6c0, coex_dm->cur_val0x6c4,
			 coex_dm->cur_val0x6c8, coex_dm->cur_val0x6cc);

		if ((coex_dm->pre_val0x6c0 == coex_dm->cur_val0x6c0) &&
		    (coex_dm->pre_val0x6c4 == coex_dm->cur_val0x6c4) &&
		    (coex_dm->pre_val0x6c8 == coex_dm->cur_val0x6c8) &&
		    (coex_dm->pre_val0x6cc == coex_dm->cur_val0x6cc))
			return;
	}
	btc8723b2ant_set_coex_table(btcoexist, val0x6c0, val0x6c4,
				    val0x6c8, val0x6cc);

	coex_dm->pre_val0x6c0 = coex_dm->cur_val0x6c0;
	coex_dm->pre_val0x6c4 = coex_dm->cur_val0x6c4;
	coex_dm->pre_val0x6c8 = coex_dm->cur_val0x6c8;
	coex_dm->pre_val0x6cc = coex_dm->cur_val0x6cc;
}