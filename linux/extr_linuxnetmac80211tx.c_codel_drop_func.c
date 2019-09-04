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
struct TYPE_3__ {int /*<<< orphan*/  vif; } ;
struct txq_info {TYPE_1__ txq; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_local {struct ieee80211_hw hw; } ;
struct TYPE_4__ {struct ieee80211_local* local; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 TYPE_2__* vif_to_sdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void codel_drop_func(struct sk_buff *skb,
			    void *ctx)
{
	struct ieee80211_local *local;
	struct ieee80211_hw *hw;
	struct txq_info *txqi;

	txqi = ctx;
	local = vif_to_sdata(txqi->txq.vif)->local;
	hw = &local->hw;

	ieee80211_free_txskb(hw, skb);
}