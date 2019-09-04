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
struct spi_master {scalar_t__ dma_rx; scalar_t__ dma_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 

__attribute__((used)) static void rspi_release_dma(struct spi_master *master)
{
	if (master->dma_tx)
		dma_release_channel(master->dma_tx);
	if (master->dma_rx)
		dma_release_channel(master->dma_rx);
}