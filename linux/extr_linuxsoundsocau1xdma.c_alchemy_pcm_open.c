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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {int stream; struct snd_soc_pcm_runtime* private_data; } ;
struct alchemy_pcm_ctx {TYPE_1__* stream; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; struct snd_pcm_substream* substream; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int DMA_NC ; 
 int ENODEV ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  alchemy_pcm_hardware ; 
 int /*<<< orphan*/  au1000_dma_interrupt ; 
 int get_dma_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_au1000_dma (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int) ; 
 int* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 struct alchemy_pcm_ctx* ss_to_ctx (struct snd_pcm_substream*) ; 

__attribute__((used)) static int alchemy_pcm_open(struct snd_pcm_substream *substream)
{
	struct alchemy_pcm_ctx *ctx = ss_to_ctx(substream);
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int *dmaids, s = substream->stream;
	char *name;

	dmaids = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
	if (!dmaids)
		return -ENODEV;	/* whoa, has ordering changed? */

	/* DMA setup */
	name = (s == SNDRV_PCM_STREAM_PLAYBACK) ? "audio-tx" : "audio-rx";
	ctx->stream[s].dma = request_au1000_dma(dmaids[s], name,
					au1000_dma_interrupt, 0,
					&ctx->stream[s]);
	set_dma_mode(ctx->stream[s].dma,
		     get_dma_mode(ctx->stream[s].dma) & ~DMA_NC);

	ctx->stream[s].substream = substream;
	ctx->stream[s].buffer = NULL;
	snd_soc_set_runtime_hwparams(substream, &alchemy_pcm_hardware);

	return 0;
}