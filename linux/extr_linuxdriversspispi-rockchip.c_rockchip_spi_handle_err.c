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
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ch; } ;
struct TYPE_3__ {int /*<<< orphan*/  ch; } ;
struct rockchip_spi {int state; int /*<<< orphan*/  lock; TYPE_2__ dma_tx; TYPE_1__ dma_rx; scalar_t__ use_dma; } ;

/* Variables and functions */
 int RXBUSY ; 
 int TXBUSY ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_fifo (struct rockchip_spi*) ; 
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rockchip_spi_handle_err(struct spi_master *master,
				    struct spi_message *msg)
{
	unsigned long flags;
	struct rockchip_spi *rs = spi_master_get_devdata(master);

	spin_lock_irqsave(&rs->lock, flags);

	/*
	 * For DMA mode, we need terminate DMA channel and flush
	 * fifo for the next transfer if DMA thansfer timeout.
	 * handle_err() was called by core if transfer failed.
	 * Maybe it is reasonable for error handling here.
	 */
	if (rs->use_dma) {
		if (rs->state & RXBUSY) {
			dmaengine_terminate_async(rs->dma_rx.ch);
			flush_fifo(rs);
		}

		if (rs->state & TXBUSY)
			dmaengine_terminate_async(rs->dma_tx.ch);
	}

	spin_unlock_irqrestore(&rs->lock, flags);
}