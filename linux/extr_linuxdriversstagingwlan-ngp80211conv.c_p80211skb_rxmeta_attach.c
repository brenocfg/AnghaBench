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
struct wlandevice {int /*<<< orphan*/  name; int /*<<< orphan*/  netdev; } ;
struct sk_buff {scalar_t__ cb; } ;
struct p80211_rxmeta {int /*<<< orphan*/  hosttime; struct wlandevice* wlandev; } ;
struct p80211_frmmeta {struct p80211_rxmeta* rx; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  P80211_FRMMETA_MAGIC ; 
 int /*<<< orphan*/  jiffies ; 
 struct p80211_rxmeta* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ p80211skb_rxmeta (struct sk_buff*) ; 

int p80211skb_rxmeta_attach(struct wlandevice *wlandev, struct sk_buff *skb)
{
	int result = 0;
	struct p80211_rxmeta *rxmeta;
	struct p80211_frmmeta *frmmeta;

	/* If these already have metadata, we error out! */
	if (p80211skb_rxmeta(skb)) {
		netdev_err(wlandev->netdev,
			   "%s: RXmeta already attached!\n", wlandev->name);
		result = 0;
		goto exit;
	}

	/* Allocate the rxmeta */
	rxmeta = kzalloc(sizeof(*rxmeta), GFP_ATOMIC);

	if (!rxmeta) {
		result = 1;
		goto exit;
	}

	/* Initialize the rxmeta */
	rxmeta->wlandev = wlandev;
	rxmeta->hosttime = jiffies;

	/* Overlay a frmmeta_t onto skb->cb */
	memset(skb->cb, 0, sizeof(struct p80211_frmmeta));
	frmmeta = (struct p80211_frmmeta *)(skb->cb);
	frmmeta->magic = P80211_FRMMETA_MAGIC;
	frmmeta->rx = rxmeta;
exit:
	return result;
}