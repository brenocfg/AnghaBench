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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  period_bytes_max; int /*<<< orphan*/  buffer_bytes_max; } ;
struct snd_pcm_runtime {TYPE_2__ hw; int /*<<< orphan*/  private_free; struct gus_pcm_private* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma1; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;
struct gus_pcm_private {struct snd_pcm_substream* substream; int /*<<< orphan*/  flags; int /*<<< orphan*/  dma_count; int /*<<< orphan*/  sleep; int /*<<< orphan*/  lock; struct snd_gus_card* gus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_GF1_PCM_PFLG_NONE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct gus_pcm_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snd_gf1_dma_init (struct snd_gus_card*) ; 
 TYPE_2__ snd_gf1_pcm_playback ; 
 int /*<<< orphan*/  snd_gf1_pcm_playback_free ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_limit_isa_dma_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_gus_card* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_gf1_pcm_playback_open(struct snd_pcm_substream *substream)
{
	struct gus_pcm_private *pcmp;
	struct snd_gus_card *gus = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	pcmp = kzalloc(sizeof(*pcmp), GFP_KERNEL);
	if (pcmp == NULL)
		return -ENOMEM;
	pcmp->gus = gus;
	spin_lock_init(&pcmp->lock);
	init_waitqueue_head(&pcmp->sleep);
	atomic_set(&pcmp->dma_count, 0);

	runtime->private_data = pcmp;
	runtime->private_free = snd_gf1_pcm_playback_free;

#if 0
	printk(KERN_DEBUG "playback.buffer = 0x%lx, gf1.pcm_buffer = 0x%lx\n",
	       (long) pcm->playback.buffer, (long) gus->gf1.pcm_buffer);
#endif
	if ((err = snd_gf1_dma_init(gus)) < 0)
		return err;
	pcmp->flags = SNDRV_GF1_PCM_PFLG_NONE;
	pcmp->substream = substream;
	runtime->hw = snd_gf1_pcm_playback;
	snd_pcm_limit_isa_dma_size(gus->gf1.dma1, &runtime->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(gus->gf1.dma1, &runtime->hw.period_bytes_max);
	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64);
	return 0;
}