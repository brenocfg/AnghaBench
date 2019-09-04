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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  __ieee80211_tx_skb_tid_band (struct ieee80211_sub_if_data*,struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline void
ieee80211_tx_skb_tid_band(struct ieee80211_sub_if_data *sdata,
			  struct sk_buff *skb, int tid,
			  enum nl80211_band band, u32 txdata_flags)
{
	rcu_read_lock();
	__ieee80211_tx_skb_tid_band(sdata, skb, tid, band, txdata_flags);
	rcu_read_unlock();
}