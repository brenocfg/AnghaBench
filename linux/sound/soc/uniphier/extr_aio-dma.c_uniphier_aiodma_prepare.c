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
struct uniphier_aio_sub {int /*<<< orphan*/  lock; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {size_t stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; int channels; scalar_t__ dma_bytes; scalar_t__ dma_addr; } ;

/* Variables and functions */
 int aiodma_ch_set_param (struct uniphier_aio_sub*) ; 
 int aiodma_rb_set_buffer (struct uniphier_aio_sub*,scalar_t__,scalar_t__,int) ; 
 int samples_to_bytes (struct snd_pcm_runtime*,int) ; 
 struct snd_soc_pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_aiodma_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = snd_pcm_substream_chip(substream);
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[substream->stream];
	int bytes = runtime->period_size *
		runtime->channels * samples_to_bytes(runtime, 1);
	unsigned long flags;
	int ret;

	ret = aiodma_ch_set_param(sub);
	if (ret)
		return ret;

	spin_lock_irqsave(&sub->lock, flags);
	ret = aiodma_rb_set_buffer(sub, runtime->dma_addr,
				   runtime->dma_addr + runtime->dma_bytes,
				   bytes);
	spin_unlock_irqrestore(&sub->lock, flags);
	if (ret)
		return ret;

	return 0;
}