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
struct wlandevice {int /*<<< orphan*/  netdev; } ;
struct sk_buff {int dummy; } ;
struct p80211_frmmeta {scalar_t__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,struct sk_buff*) ; 
 struct p80211_frmmeta* p80211skb_frmmeta (struct sk_buff*) ; 
 int /*<<< orphan*/  p80211skb_rxmeta_detach (struct sk_buff*) ; 

void p80211skb_free(struct wlandevice *wlandev, struct sk_buff *skb)
{
	struct p80211_frmmeta *meta;

	meta = p80211skb_frmmeta(skb);
	if (meta && meta->rx)
		p80211skb_rxmeta_detach(skb);
	else
		netdev_err(wlandev->netdev,
			   "Freeing an skb (%p) w/ no frmmeta.\n", skb);
	dev_kfree_skb(skb);
}