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
typedef  int u64 ;
struct tx_ring_info {struct tx_buff_info* tx_buffs; int /*<<< orphan*/  mark_pending; int /*<<< orphan*/ * descr; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct tx_pkt_hdr {int /*<<< orphan*/  flags; } ;
struct tx_buff_info {int /*<<< orphan*/  mapping; struct sk_buff* skb; } ;
struct sk_buff {scalar_t__ data; } ;
struct niu {int /*<<< orphan*/  device; TYPE_1__* ops; } ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unmap_page ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* unmap_single ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MAX_TX_DESC_LEN ; 
 int NEXT_TX (struct tx_ring_info*,int) ; 
 int TXHDR_LEN ; 
 int TXHDR_LEN_SHIFT ; 
 int TXHDR_PAD ; 
 int TX_DESC_MARK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int release_tx_packet(struct niu *np, struct tx_ring_info *rp, int idx)
{
	struct tx_buff_info *tb = &rp->tx_buffs[idx];
	struct sk_buff *skb = tb->skb;
	struct tx_pkt_hdr *tp;
	u64 tx_flags;
	int i, len;

	tp = (struct tx_pkt_hdr *) skb->data;
	tx_flags = le64_to_cpup(&tp->flags);

	rp->tx_packets++;
	rp->tx_bytes += (((tx_flags & TXHDR_LEN) >> TXHDR_LEN_SHIFT) -
			 ((tx_flags & TXHDR_PAD) / 2));

	len = skb_headlen(skb);
	np->ops->unmap_single(np->device, tb->mapping,
			      len, DMA_TO_DEVICE);

	if (le64_to_cpu(rp->descr[idx]) & TX_DESC_MARK)
		rp->mark_pending--;

	tb->skb = NULL;
	do {
		idx = NEXT_TX(rp, idx);
		len -= MAX_TX_DESC_LEN;
	} while (len > 0);

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		tb = &rp->tx_buffs[idx];
		BUG_ON(tb->skb != NULL);
		np->ops->unmap_page(np->device, tb->mapping,
				    skb_frag_size(&skb_shinfo(skb)->frags[i]),
				    DMA_TO_DEVICE);
		idx = NEXT_TX(rp, idx);
	}

	dev_kfree_skb(skb);

	return idx;
}