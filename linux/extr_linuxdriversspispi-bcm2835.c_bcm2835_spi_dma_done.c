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
struct spi_master {int /*<<< orphan*/  xfer_completion; int /*<<< orphan*/  dma_tx; } ;
struct bcm2835_spi {int /*<<< orphan*/  dma_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_master*) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void bcm2835_spi_dma_done(void *data)
{
	struct spi_master *master = data;
	struct bcm2835_spi *bs = spi_master_get_devdata(master);

	/* reset fifo and HW */
	bcm2835_spi_reset_hw(master);

	/* and terminate tx-dma as we do not have an irq for it
	 * because when the rx dma will terminate and this callback
	 * is called the tx-dma must have finished - can't get to this
	 * situation otherwise...
	 */
	if (cmpxchg(&bs->dma_pending, true, false)) {
		dmaengine_terminate_all(master->dma_tx);
	}

	/* and mark as completed */;
	complete(&master->xfer_completion);
}