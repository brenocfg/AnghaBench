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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct dmaengine_pcm_runtime_data {int /*<<< orphan*/  cookie; int /*<<< orphan*/  dma_chan; } ;
struct dma_tx_state {unsigned int residue; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;

/* Variables and functions */
 int DMA_IN_PROGRESS ; 
 int DMA_PAUSED ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,unsigned int) ; 
 int dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 unsigned int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct dmaengine_pcm_runtime_data* substream_to_prtd (struct snd_pcm_substream*) ; 

snd_pcm_uframes_t snd_dmaengine_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);
	struct dma_tx_state state;
	enum dma_status status;
	unsigned int buf_size;
	unsigned int pos = 0;

	status = dmaengine_tx_status(prtd->dma_chan, prtd->cookie, &state);
	if (status == DMA_IN_PROGRESS || status == DMA_PAUSED) {
		buf_size = snd_pcm_lib_buffer_bytes(substream);
		if (state.residue > 0 && state.residue <= buf_size)
			pos = buf_size - state.residue;
	}

	return bytes_to_frames(substream->runtime, pos);
}