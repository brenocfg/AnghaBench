#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_7__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_3__ stats; } ;
struct TYPE_6__ {scalar_t__ dual_emac; } ;
struct cpsw_common {TYPE_4__* rxv; int /*<<< orphan*/  cpts; int /*<<< orphan*/  rx_packet_max; scalar_t__ usage_count; TYPE_2__ data; TYPE_1__* slaves; } ;
struct cpdma_chan {int dummy; } ;
struct TYPE_8__ {struct cpdma_chan* ch; } ;
struct TYPE_5__ {struct net_device* ndev; } ;

/* Variables and functions */
 int CPDMA_RX_SOURCE_PORT (int) ; 
 int CPDMA_RX_VLAN_ENCAP ; 
 scalar_t__ WARN_ON (int) ; 
 int cpdma_chan_submit (struct cpdma_chan*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_rx_vlan_encap (struct sk_buff*) ; 
 int /*<<< orphan*/  cpts_rx_timestamp (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  kmemleak_not_leak (struct sk_buff*) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_dormant (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_queue_mapping (struct sk_buff*,struct sk_buff*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cpsw_rx_handler(void *token, int len, int status)
{
	struct cpdma_chan	*ch;
	struct sk_buff		*skb = token;
	struct sk_buff		*new_skb;
	struct net_device	*ndev = skb->dev;
	int			ret = 0, port;
	struct cpsw_common	*cpsw = ndev_to_cpsw(ndev);

	if (cpsw->data.dual_emac) {
		port = CPDMA_RX_SOURCE_PORT(status);
		if (port) {
			ndev = cpsw->slaves[--port].ndev;
			skb->dev = ndev;
		}
	}

	if (unlikely(status < 0) || unlikely(!netif_running(ndev))) {
		/* In dual emac mode check for all interfaces */
		if (cpsw->data.dual_emac && cpsw->usage_count &&
		    (status >= 0)) {
			/* The packet received is for the interface which
			 * is already down and the other interface is up
			 * and running, instead of freeing which results
			 * in reducing of the number of rx descriptor in
			 * DMA engine, requeue skb back to cpdma.
			 */
			new_skb = skb;
			goto requeue;
		}

		/* the interface is going down, skbs are purged */
		dev_kfree_skb_any(skb);
		return;
	}

	new_skb = netdev_alloc_skb_ip_align(ndev, cpsw->rx_packet_max);
	if (new_skb) {
		skb_copy_queue_mapping(new_skb, skb);
		skb_put(skb, len);
		if (status & CPDMA_RX_VLAN_ENCAP)
			cpsw_rx_vlan_encap(skb);
		cpts_rx_timestamp(cpsw->cpts, skb);
		skb->protocol = eth_type_trans(skb, ndev);
		netif_receive_skb(skb);
		ndev->stats.rx_bytes += len;
		ndev->stats.rx_packets++;
		kmemleak_not_leak(new_skb);
	} else {
		ndev->stats.rx_dropped++;
		new_skb = skb;
	}

requeue:
	if (netif_dormant(ndev)) {
		dev_kfree_skb_any(new_skb);
		return;
	}

	ch = cpsw->rxv[skb_get_queue_mapping(new_skb)].ch;
	ret = cpdma_chan_submit(ch, new_skb, new_skb->data,
				skb_tailroom(new_skb), 0);
	if (WARN_ON(ret < 0))
		dev_kfree_skb_any(new_skb);
}