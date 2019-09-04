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
struct TYPE_2__ {size_t size; int /*<<< orphan*/ * vaddr_txbuff_32; int /*<<< orphan*/  paddr; } ;
struct ath10k_htt {TYPE_1__ txbuf; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_htt_tx_free_cont_txbuf_32(struct ath10k_htt *htt)
{
	struct ath10k *ar = htt->ar;
	size_t size;

	if (!htt->txbuf.vaddr_txbuff_32)
		return;

	size = htt->txbuf.size;
	dma_free_coherent(ar->dev, size, htt->txbuf.vaddr_txbuff_32,
			  htt->txbuf.paddr);
	htt->txbuf.vaddr_txbuff_32 = NULL;
}