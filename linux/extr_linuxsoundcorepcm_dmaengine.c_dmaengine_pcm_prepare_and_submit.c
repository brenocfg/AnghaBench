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
struct dmaengine_pcm_runtime_data {int /*<<< orphan*/  cookie; scalar_t__ pos; struct dma_chan* dma_chan; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {struct snd_pcm_substream* callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  no_period_wakeup; } ;

/* Variables and functions */
 unsigned long DMA_CTRL_ACK ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dmaengine_pcm_dma_complete ; 
 struct dma_async_tx_descriptor* dmaengine_prep_dma_cyclic (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_substream_to_dma_direction (struct snd_pcm_substream*) ; 
 struct dmaengine_pcm_runtime_data* substream_to_prtd (struct snd_pcm_substream*) ; 

__attribute__((used)) static int dmaengine_pcm_prepare_and_submit(struct snd_pcm_substream *substream)
{
	struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);
	struct dma_chan *chan = prtd->dma_chan;
	struct dma_async_tx_descriptor *desc;
	enum dma_transfer_direction direction;
	unsigned long flags = DMA_CTRL_ACK;

	direction = snd_pcm_substream_to_dma_direction(substream);

	if (!substream->runtime->no_period_wakeup)
		flags |= DMA_PREP_INTERRUPT;

	prtd->pos = 0;
	desc = dmaengine_prep_dma_cyclic(chan,
		substream->runtime->dma_addr,
		snd_pcm_lib_buffer_bytes(substream),
		snd_pcm_lib_period_bytes(substream), direction, flags);

	if (!desc)
		return -ENOMEM;

	desc->callback = dmaengine_pcm_dma_complete;
	desc->callback_param = substream;
	prtd->cookie = dmaengine_submit(desc);

	return 0;
}