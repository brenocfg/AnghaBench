#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct xenvif_queue {TYPE_2__* vif; TYPE_1__ stats; } ;
struct xenvif_pkt_state {int frag; int /*<<< orphan*/  extra_count; struct xen_netif_extra_info* extras; scalar_t__ remaining_len; struct sk_buff* frag_iter; struct sk_buff* skb; } ;
struct TYPE_10__ {scalar_t__ value; int /*<<< orphan*/  type; int /*<<< orphan*/  algorithm; } ;
struct TYPE_9__ {unsigned int type; scalar_t__ features; scalar_t__ pad; int /*<<< orphan*/  size; } ;
struct TYPE_11__ {TYPE_4__ hash; TYPE_3__ gso; } ;
struct xen_netif_extra_info {int type; scalar_t__ flags; TYPE_5__ u; } ;
struct sk_buff {scalar_t__ protocol; scalar_t__ l4_hash; scalar_t__ sw_hash; scalar_t__ len; } ;
struct TYPE_12__ {int /*<<< orphan*/  gso_size; } ;
struct TYPE_8__ {int gso_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ ; 
 int XEN_NETIF_EXTRA_TYPE_GSO ; 
 int XEN_NETIF_EXTRA_TYPE_HASH ; 
 int /*<<< orphan*/  _XEN_NETIF_CTRL_HASH_TYPE_IPV4 ; 
 int /*<<< orphan*/  _XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP ; 
 int /*<<< orphan*/  _XEN_NETIF_CTRL_HASH_TYPE_IPV6 ; 
 int /*<<< orphan*/  _XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xenvif_pkt_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_get_hash_raw (struct sk_buff*) ; 
 TYPE_6__* skb_shinfo (struct sk_buff*) ; 
 unsigned int xenvif_gso_type (struct sk_buff*) ; 
 struct sk_buff* xenvif_rx_dequeue (struct xenvif_queue*) ; 

__attribute__((used)) static void xenvif_rx_next_skb(struct xenvif_queue *queue,
			       struct xenvif_pkt_state *pkt)
{
	struct sk_buff *skb;
	unsigned int gso_type;

	skb = xenvif_rx_dequeue(queue);

	queue->stats.tx_bytes += skb->len;
	queue->stats.tx_packets++;

	/* Reset packet state. */
	memset(pkt, 0, sizeof(struct xenvif_pkt_state));

	pkt->skb = skb;
	pkt->frag_iter = skb;
	pkt->remaining_len = skb->len;
	pkt->frag = -1;

	gso_type = xenvif_gso_type(skb);
	if ((1 << gso_type) & queue->vif->gso_mask) {
		struct xen_netif_extra_info *extra;

		extra = &pkt->extras[XEN_NETIF_EXTRA_TYPE_GSO - 1];

		extra->u.gso.type = gso_type;
		extra->u.gso.size = skb_shinfo(skb)->gso_size;
		extra->u.gso.pad = 0;
		extra->u.gso.features = 0;
		extra->type = XEN_NETIF_EXTRA_TYPE_GSO;
		extra->flags = 0;

		pkt->extra_count++;
	}

	if (skb->sw_hash) {
		struct xen_netif_extra_info *extra;

		extra = &pkt->extras[XEN_NETIF_EXTRA_TYPE_HASH - 1];

		extra->u.hash.algorithm =
			XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ;

		if (skb->l4_hash)
			extra->u.hash.type =
				skb->protocol == htons(ETH_P_IP) ?
				_XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP :
				_XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP;
		else
			extra->u.hash.type =
				skb->protocol == htons(ETH_P_IP) ?
				_XEN_NETIF_CTRL_HASH_TYPE_IPV4 :
				_XEN_NETIF_CTRL_HASH_TYPE_IPV6;

		*(uint32_t *)extra->u.hash.value = skb_get_hash_raw(skb);

		extra->type = XEN_NETIF_EXTRA_TYPE_HASH;
		extra->flags = 0;

		pkt->extra_count++;
	}
}