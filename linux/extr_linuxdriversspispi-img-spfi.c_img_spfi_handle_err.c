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
struct spi_message {int dummy; } ;
struct spi_master {int dummy; } ;
struct img_spfi {int tx_dma_busy; int rx_dma_busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_ch; int /*<<< orphan*/  tx_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct img_spfi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void img_spfi_handle_err(struct spi_master *master,
				struct spi_message *msg)
{
	struct img_spfi *spfi = spi_master_get_devdata(master);
	unsigned long flags;

	/*
	 * Stop all DMA and reset the controller if the previous transaction
	 * timed-out and never completed it's DMA.
	 */
	spin_lock_irqsave(&spfi->lock, flags);
	if (spfi->tx_dma_busy || spfi->rx_dma_busy) {
		spfi->tx_dma_busy = false;
		spfi->rx_dma_busy = false;

		dmaengine_terminate_all(spfi->tx_ch);
		dmaengine_terminate_all(spfi->rx_ch);
	}
	spin_unlock_irqrestore(&spfi->lock, flags);
}