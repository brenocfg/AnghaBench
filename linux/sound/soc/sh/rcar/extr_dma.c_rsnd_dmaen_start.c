#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dmaen {scalar_t__ cookie; int /*<<< orphan*/  chan; int /*<<< orphan*/  dma_len; } ;
struct rsnd_dma {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct rsnd_dai_stream {struct snd_pcm_substream* substream; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; void* dst_addr_width; void* src_addr_width; int /*<<< orphan*/  direction; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_dma_cyclic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct dma_slave_config*) ; 
 scalar_t__ dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 struct rsnd_dmaen* rsnd_dma_to_dmaen (struct rsnd_dma*) ; 
 int /*<<< orphan*/  rsnd_dmaen_complete ; 
 int rsnd_io_is_play (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_mod_get (struct rsnd_dma*) ; 
 int /*<<< orphan*/  rsnd_mod_name (struct rsnd_mod*) ; 
 struct rsnd_dma* rsnd_mod_to_dma (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static int rsnd_dmaen_start(struct rsnd_mod *mod,
			    struct rsnd_dai_stream *io,
			    struct rsnd_priv *priv)
{
	struct rsnd_dma *dma = rsnd_mod_to_dma(mod);
	struct rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);
	struct snd_pcm_substream *substream = io->substream;
	struct device *dev = rsnd_priv_to_dev(priv);
	struct dma_async_tx_descriptor *desc;
	struct dma_slave_config cfg = {};
	int is_play = rsnd_io_is_play(io);
	int ret;

	cfg.direction	= is_play ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	cfg.src_addr	= dma->src_addr;
	cfg.dst_addr	= dma->dst_addr;
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	dev_dbg(dev, "%s %pad -> %pad\n",
		rsnd_mod_name(mod),
		&cfg.src_addr, &cfg.dst_addr);

	ret = dmaengine_slave_config(dmaen->chan, &cfg);
	if (ret < 0)
		return ret;

	desc = dmaengine_prep_dma_cyclic(dmaen->chan,
					 substream->runtime->dma_addr,
					 snd_pcm_lib_buffer_bytes(substream),
					 snd_pcm_lib_period_bytes(substream),
					 is_play ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	if (!desc) {
		dev_err(dev, "dmaengine_prep_slave_sg() fail\n");
		return -EIO;
	}

	desc->callback		= rsnd_dmaen_complete;
	desc->callback_param	= rsnd_mod_get(dma);

	dmaen->dma_len		= snd_pcm_lib_buffer_bytes(substream);

	dmaen->cookie = dmaengine_submit(desc);
	if (dmaen->cookie < 0) {
		dev_err(dev, "dmaengine_submit() fail\n");
		return -EIO;
	}

	dma_async_issue_pending(dmaen->chan);

	return 0;
}