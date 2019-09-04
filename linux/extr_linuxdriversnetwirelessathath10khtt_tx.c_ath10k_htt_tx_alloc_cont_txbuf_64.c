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
struct ath10k_htt_txbuf_64 {int dummy; } ;
struct TYPE_2__ {size_t size; int /*<<< orphan*/  vaddr_txbuff_64; int /*<<< orphan*/  paddr; } ;
struct ath10k_htt {int max_num_pending_tx; TYPE_1__ txbuf; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_htt_tx_alloc_cont_txbuf_64(struct ath10k_htt *htt)
{
	struct ath10k *ar = htt->ar;
	size_t size;

	size = htt->max_num_pending_tx *
			sizeof(struct ath10k_htt_txbuf_64);

	htt->txbuf.vaddr_txbuff_64 = dma_alloc_coherent(ar->dev, size,
							&htt->txbuf.paddr,
							GFP_KERNEL);
	if (!htt->txbuf.vaddr_txbuff_64)
		return -ENOMEM;

	htt->txbuf.size = size;

	return 0;
}