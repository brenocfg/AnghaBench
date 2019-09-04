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
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  name; } ;
struct ieee80211_rx_data {struct sk_buff* skb; TYPE_1__* sta; struct ieee80211_sub_if_data* sdata; struct ieee80211_local* local; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
struct ieee80211_fast_rx {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fast_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ieee80211_accept_frame (struct ieee80211_rx_data*) ; 
 scalar_t__ ieee80211_invoke_fast_rx (struct ieee80211_rx_data*,struct ieee80211_fast_rx*) ; 
 int /*<<< orphan*/  ieee80211_invoke_rx_handlers (struct ieee80211_rx_data*) ; 
 scalar_t__ net_ratelimit () ; 
 struct ieee80211_fast_rx* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_prepare_and_rx_handle(struct ieee80211_rx_data *rx,
					    struct sk_buff *skb, bool consume)
{
	struct ieee80211_local *local = rx->local;
	struct ieee80211_sub_if_data *sdata = rx->sdata;

	rx->skb = skb;

	/* See if we can do fast-rx; if we have to copy we already lost,
	 * so punt in that case. We should never have to deliver a data
	 * frame to multiple interfaces anyway.
	 *
	 * We skip the ieee80211_accept_frame() call and do the necessary
	 * checking inside ieee80211_invoke_fast_rx().
	 */
	if (consume && rx->sta) {
		struct ieee80211_fast_rx *fast_rx;

		fast_rx = rcu_dereference(rx->sta->fast_rx);
		if (fast_rx && ieee80211_invoke_fast_rx(rx, fast_rx))
			return true;
	}

	if (!ieee80211_accept_frame(rx))
		return false;

	if (!consume) {
		skb = skb_copy(skb, GFP_ATOMIC);
		if (!skb) {
			if (net_ratelimit())
				wiphy_debug(local->hw.wiphy,
					"failed to copy skb for %s\n",
					sdata->name);
			return true;
		}

		rx->skb = skb;
	}

	ieee80211_invoke_rx_handlers(rx);
	return true;
}