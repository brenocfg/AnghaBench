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
struct spi_master {void* dma_tx; void* dma_rx; } ;
struct pic32_spi {int /*<<< orphan*/  flags; struct spi_master* master; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int /*<<< orphan*/  PIC32F_DMA_PREP ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_slave_channel_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*,char*) ; 
 scalar_t__ pic32_spi_dma_config (struct pic32_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pic32_spi_dma_prep(struct pic32_spi *pic32s, struct device *dev)
{
	struct spi_master *master = pic32s->master;
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	master->dma_rx = dma_request_slave_channel_compat(mask, NULL, NULL,
							  dev, "spi-rx");
	if (!master->dma_rx) {
		dev_warn(dev, "RX channel not found.\n");
		goto out_err;
	}

	master->dma_tx = dma_request_slave_channel_compat(mask, NULL, NULL,
							  dev, "spi-tx");
	if (!master->dma_tx) {
		dev_warn(dev, "TX channel not found.\n");
		goto out_err;
	}

	if (pic32_spi_dma_config(pic32s, DMA_SLAVE_BUSWIDTH_1_BYTE))
		goto out_err;

	/* DMA chnls allocated and prepared */
	set_bit(PIC32F_DMA_PREP, &pic32s->flags);

	return;

out_err:
	if (master->dma_rx)
		dma_release_channel(master->dma_rx);

	if (master->dma_tx)
		dma_release_channel(master->dma_tx);
}