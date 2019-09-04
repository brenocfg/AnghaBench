#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ch; int /*<<< orphan*/  direction; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  ch; int /*<<< orphan*/  direction; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_7__ {int max_burst; } ;
struct TYPE_6__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct rockchip_spi {TYPE_5__ dma_tx; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_4__ dma_rx; TYPE_3__ tx_sg; TYPE_2__ dma_caps; int /*<<< orphan*/  n_bytes; scalar_t__ tx; TYPE_1__ rx_sg; scalar_t__ rx; } ;
struct dma_slave_config {int src_maxburst; int dst_maxburst; int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  direction; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  src_addr; } ;
struct dma_async_tx_descriptor {struct rockchip_spi* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int EINVAL ; 
 int /*<<< orphan*/  RXBUSY ; 
 int /*<<< orphan*/  TXBUSY ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_spi_dma_rxcb ; 
 int /*<<< orphan*/  rockchip_spi_dma_txcb ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rockchip_spi_prepare_dma(struct rockchip_spi *rs)
{
	unsigned long flags;
	struct dma_slave_config rxconf, txconf;
	struct dma_async_tx_descriptor *rxdesc, *txdesc;

	spin_lock_irqsave(&rs->lock, flags);
	rs->state &= ~RXBUSY;
	rs->state &= ~TXBUSY;
	spin_unlock_irqrestore(&rs->lock, flags);

	rxdesc = NULL;
	if (rs->rx) {
		rxconf.direction = rs->dma_rx.direction;
		rxconf.src_addr = rs->dma_rx.addr;
		rxconf.src_addr_width = rs->n_bytes;
		if (rs->dma_caps.max_burst > 4)
			rxconf.src_maxburst = 4;
		else
			rxconf.src_maxburst = 1;
		dmaengine_slave_config(rs->dma_rx.ch, &rxconf);

		rxdesc = dmaengine_prep_slave_sg(
				rs->dma_rx.ch,
				rs->rx_sg.sgl, rs->rx_sg.nents,
				rs->dma_rx.direction, DMA_PREP_INTERRUPT);
		if (!rxdesc)
			return -EINVAL;

		rxdesc->callback = rockchip_spi_dma_rxcb;
		rxdesc->callback_param = rs;
	}

	txdesc = NULL;
	if (rs->tx) {
		txconf.direction = rs->dma_tx.direction;
		txconf.dst_addr = rs->dma_tx.addr;
		txconf.dst_addr_width = rs->n_bytes;
		if (rs->dma_caps.max_burst > 4)
			txconf.dst_maxburst = 4;
		else
			txconf.dst_maxburst = 1;
		dmaengine_slave_config(rs->dma_tx.ch, &txconf);

		txdesc = dmaengine_prep_slave_sg(
				rs->dma_tx.ch,
				rs->tx_sg.sgl, rs->tx_sg.nents,
				rs->dma_tx.direction, DMA_PREP_INTERRUPT);
		if (!txdesc) {
			if (rxdesc)
				dmaengine_terminate_sync(rs->dma_rx.ch);
			return -EINVAL;
		}

		txdesc->callback = rockchip_spi_dma_txcb;
		txdesc->callback_param = rs;
	}

	/* rx must be started before tx due to spi instinct */
	if (rxdesc) {
		spin_lock_irqsave(&rs->lock, flags);
		rs->state |= RXBUSY;
		spin_unlock_irqrestore(&rs->lock, flags);
		dmaengine_submit(rxdesc);
		dma_async_issue_pending(rs->dma_rx.ch);
	}

	if (txdesc) {
		spin_lock_irqsave(&rs->lock, flags);
		rs->state |= TXBUSY;
		spin_unlock_irqrestore(&rs->lock, flags);
		dmaengine_submit(txdesc);
		dma_async_issue_pending(rs->dma_tx.ch);
	}

	return 0;
}