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
struct spi_master {int /*<<< orphan*/  dma_rx; int /*<<< orphan*/  dma_tx; } ;
struct bcm2835_spi {int /*<<< orphan*/  dma_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_spi_reset_hw (struct spi_master*) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct bcm2835_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static void bcm2835_spi_handle_err(struct spi_master *master,
				   struct spi_message *msg)
{
	struct bcm2835_spi *bs = spi_master_get_devdata(master);

	/* if an error occurred and we have an active dma, then terminate */
	if (cmpxchg(&bs->dma_pending, true, false)) {
		dmaengine_terminate_all(master->dma_tx);
		dmaengine_terminate_all(master->dma_rx);
	}
	/* and reset */
	bcm2835_spi_reset_hw(master);
}