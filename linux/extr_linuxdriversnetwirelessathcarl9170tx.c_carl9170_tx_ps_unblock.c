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
struct sk_buff {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct carl9170_sta_info {int /*<<< orphan*/  pending_frames; } ;
struct ar9170 {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 struct ieee80211_sta* __carl9170_get_tx_sta (struct ar9170*,struct sk_buff*) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_sta_block_awake (int /*<<< orphan*/ ,struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void carl9170_tx_ps_unblock(struct ar9170 *ar, struct sk_buff *skb)
{
	struct ieee80211_sta *sta;
	struct carl9170_sta_info *sta_info;

	rcu_read_lock();
	sta = __carl9170_get_tx_sta(ar, skb);
	if (unlikely(!sta))
		goto out_rcu;

	sta_info = (struct carl9170_sta_info *) sta->drv_priv;
	if (atomic_dec_return(&sta_info->pending_frames) == 0)
		ieee80211_sta_block_awake(ar->hw, sta, false);

out_rcu:
	rcu_read_unlock();
}