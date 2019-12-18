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
struct snd_pcm_runtime {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dmaen {scalar_t__ dma_len; int /*<<< orphan*/  cookie; int /*<<< orphan*/  chan; } ;
struct rsnd_dma {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct dma_tx_state {scalar_t__ residue; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;

/* Variables and functions */
 int DMA_IN_PROGRESS ; 
 int DMA_PAUSED ; 
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,unsigned int) ; 
 int dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 struct rsnd_dmaen* rsnd_dma_to_dmaen (struct rsnd_dma*) ; 
 struct snd_pcm_runtime* rsnd_io_to_runtime (struct rsnd_dai_stream*) ; 
 struct rsnd_dma* rsnd_mod_to_dma (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_dmaen_pointer(struct rsnd_mod *mod,
			      struct rsnd_dai_stream *io,
			      snd_pcm_uframes_t *pointer)
{
	struct snd_pcm_runtime *runtime = rsnd_io_to_runtime(io);
	struct rsnd_dma *dma = rsnd_mod_to_dma(mod);
	struct rsnd_dmaen *dmaen = rsnd_dma_to_dmaen(dma);
	struct dma_tx_state state;
	enum dma_status status;
	unsigned int pos = 0;

	status = dmaengine_tx_status(dmaen->chan, dmaen->cookie, &state);
	if (status == DMA_IN_PROGRESS || status == DMA_PAUSED) {
		if (state.residue > 0 && state.residue <= dmaen->dma_len)
			pos = dmaen->dma_len - state.residue;
	}
	*pointer = bytes_to_frames(runtime, pos);

	return 0;
}