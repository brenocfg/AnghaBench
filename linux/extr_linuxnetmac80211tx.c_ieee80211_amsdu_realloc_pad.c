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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_1__ hw; int /*<<< orphan*/  tx_expand_skb_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  I802_DEBUG_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool ieee80211_amsdu_realloc_pad(struct ieee80211_local *local,
					struct sk_buff *skb, int headroom)
{
	if (skb_headroom(skb) < headroom) {
		I802_DEBUG_INC(local->tx_expand_skb_head);

		if (pskb_expand_head(skb, headroom, 0, GFP_ATOMIC)) {
			wiphy_debug(local->hw.wiphy,
				    "failed to reallocate TX buffer\n");
			return false;
		}
	}

	return true;
}