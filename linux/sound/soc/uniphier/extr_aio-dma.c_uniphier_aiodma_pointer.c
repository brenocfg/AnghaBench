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
struct uniphier_aio_sub {int /*<<< orphan*/  lock; int /*<<< orphan*/  wr_offs; int /*<<< orphan*/  rd_offs; TYPE_1__* swm; } ;
struct uniphier_aio {struct uniphier_aio_sub* sub; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {size_t stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; int channels; int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_addr; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {scalar_t__ dir; } ;

/* Variables and functions */
 scalar_t__ PORT_DIR_OUTPUT ; 
 int /*<<< orphan*/  aiodma_rb_sync (struct uniphier_aio_sub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int samples_to_bytes (struct snd_pcm_runtime*,int) ; 
 struct snd_soc_pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uniphier_aio* uniphier_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t uniphier_aiodma_pointer(
					struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = snd_pcm_substream_chip(substream);
	struct uniphier_aio *aio = uniphier_priv(rtd->cpu_dai);
	struct uniphier_aio_sub *sub = &aio->sub[substream->stream];
	int bytes = runtime->period_size *
		runtime->channels * samples_to_bytes(runtime, 1);
	unsigned long flags;
	snd_pcm_uframes_t pos;

	spin_lock_irqsave(&sub->lock, flags);
	aiodma_rb_sync(sub, runtime->dma_addr, runtime->dma_bytes, bytes);

	if (sub->swm->dir == PORT_DIR_OUTPUT)
		pos = bytes_to_frames(runtime, sub->rd_offs);
	else
		pos = bytes_to_frames(runtime, sub->wr_offs);
	spin_unlock_irqrestore(&sub->lock, flags);

	return pos;
}