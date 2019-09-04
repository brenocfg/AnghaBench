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
struct temac_local {int tx_bd_tail; int /*<<< orphan*/  (* dma_out ) (struct temac_local*,int /*<<< orphan*/ ,scalar_t__) ;scalar_t__ tx_bd_p; struct cdmac_bd* tx_bd_v; } ;
struct sk_buff {scalar_t__ ip_summed; unsigned int csum_offset; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct cdmac_bd {int app0; unsigned int app1; unsigned long app4; void* len; void* phys; scalar_t__ app2; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {unsigned long nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int STS_CTRL_APP0_EOP ; 
 int STS_CTRL_APP0_SOP ; 
 size_t TX_BD_NUM ; 
 int /*<<< orphan*/  TX_TAILDESC_PTR ; 
 void* dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 unsigned int skb_checksum_start_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_frag_address (int /*<<< orphan*/ *) ; 
 void* skb_frag_size (int /*<<< orphan*/ *) ; 
 void* skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct temac_local*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ temac_check_tx_bd_space (struct temac_local*,unsigned long) ; 

__attribute__((used)) static int temac_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct cdmac_bd *cur_p;
	dma_addr_t start_p, tail_p;
	int ii;
	unsigned long num_frag;
	skb_frag_t *frag;

	num_frag = skb_shinfo(skb)->nr_frags;
	frag = &skb_shinfo(skb)->frags[0];
	start_p = lp->tx_bd_p + sizeof(*lp->tx_bd_v) * lp->tx_bd_tail;
	cur_p = &lp->tx_bd_v[lp->tx_bd_tail];

	if (temac_check_tx_bd_space(lp, num_frag)) {
		if (!netif_queue_stopped(ndev))
			netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	cur_p->app0 = 0;
	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		unsigned int csum_start_off = skb_checksum_start_offset(skb);
		unsigned int csum_index_off = csum_start_off + skb->csum_offset;

		cur_p->app0 |= 1; /* TX Checksum Enabled */
		cur_p->app1 = (csum_start_off << 16) | csum_index_off;
		cur_p->app2 = 0;  /* initial checksum seed */
	}

	cur_p->app0 |= STS_CTRL_APP0_SOP;
	cur_p->len = skb_headlen(skb);
	cur_p->phys = dma_map_single(ndev->dev.parent, skb->data,
				     skb_headlen(skb), DMA_TO_DEVICE);
	cur_p->app4 = (unsigned long)skb;

	for (ii = 0; ii < num_frag; ii++) {
		lp->tx_bd_tail++;
		if (lp->tx_bd_tail >= TX_BD_NUM)
			lp->tx_bd_tail = 0;

		cur_p = &lp->tx_bd_v[lp->tx_bd_tail];
		cur_p->phys = dma_map_single(ndev->dev.parent,
					     skb_frag_address(frag),
					     skb_frag_size(frag), DMA_TO_DEVICE);
		cur_p->len = skb_frag_size(frag);
		cur_p->app0 = 0;
		frag++;
	}
	cur_p->app0 |= STS_CTRL_APP0_EOP;

	tail_p = lp->tx_bd_p + sizeof(*lp->tx_bd_v) * lp->tx_bd_tail;
	lp->tx_bd_tail++;
	if (lp->tx_bd_tail >= TX_BD_NUM)
		lp->tx_bd_tail = 0;

	skb_tx_timestamp(skb);

	/* Kick off the transfer */
	lp->dma_out(lp, TX_TAILDESC_PTR, tail_p); /* DMA start */

	return NETDEV_TX_OK;
}