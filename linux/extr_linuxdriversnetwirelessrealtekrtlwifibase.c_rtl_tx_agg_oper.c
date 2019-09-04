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
typedef  size_t u16 ;
struct rtl_sta_info {TYPE_2__* tids; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  agg_state; } ;
struct TYPE_4__ {TYPE_1__ agg; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int EINVAL ; 
 size_t MAX_TID_COUNT ; 
 int /*<<< orphan*/  RTL_AGG_OPERATIONAL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ unlikely (int) ; 

int rtl_tx_agg_oper(struct ieee80211_hw *hw,
		struct ieee80211_sta *sta, u16 tid)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_sta_info *sta_entry = NULL;

	if (sta == NULL)
		return -EINVAL;

	RT_TRACE(rtlpriv, COMP_SEND, DBG_DMESG,
		 "on ra = %pM tid = %d\n", sta->addr, tid);

	if (unlikely(tid >= MAX_TID_COUNT))
		return -EINVAL;

	sta_entry = (struct rtl_sta_info *)sta->drv_priv;
	sta_entry->tids[tid].agg.agg_state = RTL_AGG_OPERATIONAL;

	return 0;
}