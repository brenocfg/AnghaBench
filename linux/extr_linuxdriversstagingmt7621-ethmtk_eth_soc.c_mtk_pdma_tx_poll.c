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
typedef  size_t u32 ;
struct sk_buff {scalar_t__ len; } ;
struct mtk_tx_ring {size_t tx_free_idx; int /*<<< orphan*/  tx_free_count; struct mtk_tx_buf* tx_buf; } ;
struct mtk_tx_buf {struct sk_buff* skb; } ;
struct mtk_eth {int /*<<< orphan*/ * netdev; int /*<<< orphan*/  dev; struct mtk_tx_ring tx_ring; } ;

/* Variables and functions */
 scalar_t__ DMA_DUMMY_DESC ; 
 int /*<<< orphan*/  MTK_REG_TX_DTX_IDX0 ; 
 size_t NEXT_TX_DESP_IDX (size_t) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pdma_empty_txd (struct mtk_tx_ring*) ; 
 size_t mtk_reg_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_txd_unmap (int /*<<< orphan*/ ,struct mtk_tx_buf*) ; 
 int /*<<< orphan*/  netdev_completed_queue (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int mtk_pdma_tx_poll(struct mtk_eth *eth, int budget, bool *tx_again)
{
	struct sk_buff *skb;
	struct mtk_tx_buf *tx_buf;
	int done = 0;
	u32 idx, hwidx;
	struct mtk_tx_ring *ring = &eth->tx_ring;
	unsigned int bytes = 0;

	idx = ring->tx_free_idx;
	hwidx = mtk_reg_r32(eth, MTK_REG_TX_DTX_IDX0);

	while ((idx != hwidx) && budget) {
		tx_buf = &ring->tx_buf[idx];
		skb = tx_buf->skb;

		if (!skb)
			break;

		if (skb != (struct sk_buff *)DMA_DUMMY_DESC) {
			bytes += skb->len;
			done++;
			budget--;
		}
		mtk_txd_unmap(eth->dev, tx_buf);
		idx = NEXT_TX_DESP_IDX(idx);
	}
	ring->tx_free_idx = idx;
	atomic_set(&ring->tx_free_count, mtk_pdma_empty_txd(ring));

	/* read hw index again make sure no new tx packet */
	if (idx != hwidx || idx != mtk_reg_r32(eth, MTK_REG_TX_DTX_IDX0))
		*tx_again = 1;

	if (done)
		netdev_completed_queue(*eth->netdev, done, bytes);

	return done;
}