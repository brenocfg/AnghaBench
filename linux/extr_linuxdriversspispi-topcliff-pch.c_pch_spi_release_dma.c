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
struct pch_spi_dma_ctrl {int /*<<< orphan*/ * chan_rx; int /*<<< orphan*/ * chan_tx; } ;
struct pch_spi_data {struct pch_spi_dma_ctrl dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pch_spi_release_dma(struct pch_spi_data *data)
{
	struct pch_spi_dma_ctrl *dma;

	dma = &data->dma;
	if (dma->chan_tx) {
		dma_release_channel(dma->chan_tx);
		dma->chan_tx = NULL;
	}
	if (dma->chan_rx) {
		dma_release_channel(dma->chan_rx);
		dma->chan_rx = NULL;
	}
}