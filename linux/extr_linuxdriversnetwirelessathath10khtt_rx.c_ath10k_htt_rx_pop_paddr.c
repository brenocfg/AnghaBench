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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct ath10k_skb_rxcb {int /*<<< orphan*/  paddr; int /*<<< orphan*/  hlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  fill_cnt; int /*<<< orphan*/  lock; } ;
struct ath10k_htt {struct ath10k* ar; TYPE_1__ rx_ring; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT_DUMP ; 
 struct ath10k_skb_rxcb* ATH10K_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* ath10k_htt_rx_find_skb_paddr (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *ath10k_htt_rx_pop_paddr(struct ath10k_htt *htt,
					       u64 paddr)
{
	struct ath10k *ar = htt->ar;
	struct ath10k_skb_rxcb *rxcb;
	struct sk_buff *msdu;

	lockdep_assert_held(&htt->rx_ring.lock);

	msdu = ath10k_htt_rx_find_skb_paddr(ar, paddr);
	if (!msdu)
		return NULL;

	rxcb = ATH10K_SKB_RXCB(msdu);
	hash_del(&rxcb->hlist);
	htt->rx_ring.fill_cnt--;

	dma_unmap_single(htt->ar->dev, rxcb->paddr,
			 msdu->len + skb_tailroom(msdu),
			 DMA_FROM_DEVICE);
	ath10k_dbg_dump(ar, ATH10K_DBG_HTT_DUMP, NULL, "htt rx netbuf pop: ",
			msdu->data, msdu->len + skb_tailroom(msdu));

	return msdu;
}