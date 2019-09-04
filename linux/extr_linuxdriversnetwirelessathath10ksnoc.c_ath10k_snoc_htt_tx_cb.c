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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ath10k_ce_pipe {struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 TYPE_1__* ATH10K_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ ath10k_ce_completed_send_next (struct ath10k_ce_pipe*,void**) ; 
 int /*<<< orphan*/  ath10k_htt_hif_tx_complete (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_snoc_htt_tx_cb(struct ath10k_ce_pipe *ce_state)
{
	struct ath10k *ar = ce_state->ar;
	struct sk_buff *skb;

	while (ath10k_ce_completed_send_next(ce_state, (void **)&skb) == 0) {
		if (!skb)
			continue;

		dma_unmap_single(ar->dev, ATH10K_SKB_CB(skb)->paddr,
				 skb->len, DMA_TO_DEVICE);
		ath10k_htt_hif_tx_complete(ar, skb);
	}
}