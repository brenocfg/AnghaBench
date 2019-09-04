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
struct wireless_dev {scalar_t__ iftype; } ;
struct wil_ring {int /*<<< orphan*/  size; int /*<<< orphan*/  va; } ;
struct wil6210_priv {struct wil_ring ring_rx; struct net_device* main_ndev; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; struct net_device* dev; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wil_dbg_txrx (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_netif_rx_any (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  wil_rx_refill (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_rx_reorder (struct wil6210_priv*,struct sk_buff*) ; 
 struct sk_buff* wil_vring_reap_rx (struct wil6210_priv*,struct wil_ring*) ; 

void wil_rx_handle(struct wil6210_priv *wil, int *quota)
{
	struct net_device *ndev = wil->main_ndev;
	struct wireless_dev *wdev = ndev->ieee80211_ptr;
	struct wil_ring *v = &wil->ring_rx;
	struct sk_buff *skb;

	if (unlikely(!v->va)) {
		wil_err(wil, "Rx IRQ while Rx not yet initialized\n");
		return;
	}
	wil_dbg_txrx(wil, "rx_handle\n");
	while ((*quota > 0) && (NULL != (skb = wil_vring_reap_rx(wil, v)))) {
		(*quota)--;

		/* monitor is currently supported on main interface only */
		if (wdev->iftype == NL80211_IFTYPE_MONITOR) {
			skb->dev = ndev;
			skb_reset_mac_header(skb);
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->pkt_type = PACKET_OTHERHOST;
			skb->protocol = htons(ETH_P_802_2);
			wil_netif_rx_any(skb, ndev);
		} else {
			wil_rx_reorder(wil, skb);
		}
	}
	wil_rx_refill(wil, v->size);
}