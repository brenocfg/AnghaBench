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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct fsi_stream {int /*<<< orphan*/  chan; struct snd_pcm_substream* substream; } ;
struct fsi_priv {int dummy; } ;
struct dma_async_tx_descriptor {struct fsi_stream* callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_CTL ; 
 int /*<<< orphan*/  DIFF_ST ; 
 int DMA_CTRL_ACK ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int EIO ; 
 int ERR_OVER ; 
 int /*<<< orphan*/  FIFO_CLR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_dma_cyclic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  fsi_dma_complete ; 
 struct snd_soc_dai* fsi_get_dai (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  fsi_reg_mask_set (struct fsi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsi_reg_read (struct fsi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsi_stream_is_play (struct fsi_priv*,struct fsi_stream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 

__attribute__((used)) static int fsi_dma_transfer(struct fsi_priv *fsi, struct fsi_stream *io)
{
	struct snd_soc_dai *dai = fsi_get_dai(io->substream);
	struct snd_pcm_substream *substream = io->substream;
	struct dma_async_tx_descriptor *desc;
	int is_play = fsi_stream_is_play(fsi, io);
	enum dma_transfer_direction dir;
	int ret = -EIO;

	if (is_play)
		dir = DMA_MEM_TO_DEV;
	else
		dir = DMA_DEV_TO_MEM;

	desc = dmaengine_prep_dma_cyclic(io->chan,
					 substream->runtime->dma_addr,
					 snd_pcm_lib_buffer_bytes(substream),
					 snd_pcm_lib_period_bytes(substream),
					 dir,
					 DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc) {
		dev_err(dai->dev, "dmaengine_prep_dma_cyclic() fail\n");
		goto fsi_dma_transfer_err;
	}

	desc->callback		= fsi_dma_complete;
	desc->callback_param	= io;

	if (dmaengine_submit(desc) < 0) {
		dev_err(dai->dev, "tx_submit() fail\n");
		goto fsi_dma_transfer_err;
	}

	dma_async_issue_pending(io->chan);

	/*
	 * FIXME
	 *
	 * In DMAEngine case, codec and FSI cannot be started simultaneously
	 * since FSI is using the scheduler work queue.
	 * Therefore, in capture case, probably FSI FIFO will have got
	 * overflow error in this point.
	 * in that case, DMA cannot start transfer until error was cleared.
	 */
	if (!is_play) {
		if (ERR_OVER & fsi_reg_read(fsi, DIFF_ST)) {
			fsi_reg_mask_set(fsi, DIFF_CTL, FIFO_CLR, FIFO_CLR);
			fsi_reg_write(fsi, DIFF_ST, 0);
		}
	}

	ret = 0;

fsi_dma_transfer_err:
	return ret;
}