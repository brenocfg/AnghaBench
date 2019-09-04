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
struct stmmac_tx_queue {size_t cur_tx; struct dma_desc* dma_tx; int /*<<< orphan*/ * tx_skbuff; } ;
struct stmmac_priv {struct stmmac_tx_queue* tx_queue; } ;
struct dma_desc {int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TX_SIZE ; 
 size_t STMMAC_GET_ENTRY (size_t,int /*<<< orphan*/ ) ; 
 int TSO_MAX_BUFF_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  stmmac_prepare_tso_tx_desc (struct stmmac_priv*,struct dma_desc*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_tso_allocator(struct stmmac_priv *priv, unsigned int des,
				 int total_len, bool last_segment, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	struct dma_desc *desc;
	u32 buff_size;
	int tmp_len;

	tmp_len = total_len;

	while (tmp_len > 0) {
		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, DMA_TX_SIZE);
		WARN_ON(tx_q->tx_skbuff[tx_q->cur_tx]);
		desc = tx_q->dma_tx + tx_q->cur_tx;

		desc->des0 = cpu_to_le32(des + (total_len - tmp_len));
		buff_size = tmp_len >= TSO_MAX_BUFF_SIZE ?
			    TSO_MAX_BUFF_SIZE : tmp_len;

		stmmac_prepare_tso_tx_desc(priv, desc, 0, buff_size,
				0, 1,
				(last_segment) && (tmp_len <= TSO_MAX_BUFF_SIZE),
				0, 0);

		tmp_len -= TSO_MAX_BUFF_SIZE;
	}
}