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
struct mtk_tx_ring {int dummy; } ;
struct mtk_tx_dma {int /*<<< orphan*/  txd2; } ;

/* Variables and functions */
 struct mtk_tx_dma* mtk_qdma_phys_to_virt (struct mtk_tx_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mtk_tx_dma *mtk_tx_next_qdma(struct mtk_tx_ring *ring,
					   struct mtk_tx_dma *txd)
{
	return mtk_qdma_phys_to_virt(ring, txd->txd2);
}