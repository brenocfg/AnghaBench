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
struct spi_master {int /*<<< orphan*/ * dma_rx; int /*<<< orphan*/ * dma_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_dma_release(struct spi_master *master)
{
	if (master->dma_tx) {
		dmaengine_terminate_all(master->dma_tx);
		dma_release_channel(master->dma_tx);
		master->dma_tx = NULL;
	}
	if (master->dma_rx) {
		dmaengine_terminate_all(master->dma_rx);
		dma_release_channel(master->dma_rx);
		master->dma_rx = NULL;
	}
}