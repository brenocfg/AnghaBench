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
struct fsi_stream {int /*<<< orphan*/ * chan; scalar_t__ dma_id; } ;
struct TYPE_4__ {int /*<<< orphan*/ * handler; } ;
struct TYPE_3__ {int /*<<< orphan*/ * handler; } ;
struct fsi_priv {TYPE_2__ capture; TYPE_1__ playback; scalar_t__ phys; } ;
struct dma_slave_config {int /*<<< orphan*/  direction; void* src_addr_width; scalar_t__ src_addr; void* dst_addr_width; scalar_t__ dst_addr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 scalar_t__ REG_DIDT ; 
 scalar_t__ REG_DODT ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * dma_request_slave_channel (struct device*,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ *,struct dma_slave_config*) ; 
 int /*<<< orphan*/  fsi_pio_pop_handler ; 
 int /*<<< orphan*/  fsi_pio_push_handler ; 
 int fsi_stream_is_play (struct fsi_priv*,struct fsi_stream*) ; 
 int fsi_stream_probe (struct fsi_priv*,struct device*) ; 
 int /*<<< orphan*/  shdma_chan_filter ; 

__attribute__((used)) static int fsi_dma_probe(struct fsi_priv *fsi, struct fsi_stream *io, struct device *dev)
{
	int is_play = fsi_stream_is_play(fsi, io);

#ifdef CONFIG_SUPERH
	dma_cap_mask_t mask;
	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	io->chan = dma_request_channel(mask, shdma_chan_filter,
				       (void *)io->dma_id);
#else
	io->chan = dma_request_slave_channel(dev, is_play ? "tx" : "rx");
#endif
	if (io->chan) {
		struct dma_slave_config cfg = {};
		int ret;

		if (is_play) {
			cfg.dst_addr		= fsi->phys + REG_DODT;
			cfg.dst_addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.direction		= DMA_MEM_TO_DEV;
		} else {
			cfg.src_addr		= fsi->phys + REG_DIDT;
			cfg.src_addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES;
			cfg.direction		= DMA_DEV_TO_MEM;
		}

		ret = dmaengine_slave_config(io->chan, &cfg);
		if (ret < 0) {
			dma_release_channel(io->chan);
			io->chan = NULL;
		}
	}

	if (!io->chan) {

		/* switch to PIO handler */
		if (is_play)
			fsi->playback.handler	= &fsi_pio_push_handler;
		else
			fsi->capture.handler	= &fsi_pio_pop_handler;

		dev_info(dev, "switch handler (dma => pio)\n");

		/* probe again */
		return fsi_stream_probe(fsi, dev);
	}

	return 0;
}