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
struct uniphier_aio_sub {TYPE_1__* substream; int /*<<< orphan*/  lock; scalar_t__ threshold; } ;
struct snd_pcm_runtime {int period_size; int channels; int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_2__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  aiodma_rb_clear_irq (struct uniphier_aio_sub*) ; 
 int aiodma_rb_set_threshold (struct uniphier_aio_sub*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  aiodma_rb_sync (struct uniphier_aio_sub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int samples_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aiodma_pcm_irq(struct uniphier_aio_sub *sub)
{
	struct snd_pcm_runtime *runtime = sub->substream->runtime;
	int bytes = runtime->period_size *
		runtime->channels * samples_to_bytes(runtime, 1);
	int ret;

	spin_lock(&sub->lock);
	ret = aiodma_rb_set_threshold(sub, runtime->dma_bytes,
				      sub->threshold + bytes);
	if (!ret)
		sub->threshold += bytes;

	aiodma_rb_sync(sub, runtime->dma_addr, runtime->dma_bytes, bytes);
	aiodma_rb_clear_irq(sub);
	spin_unlock(&sub->lock);

	snd_pcm_period_elapsed(sub->substream);
}