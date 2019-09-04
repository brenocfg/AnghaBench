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
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct snd_m3 {int num_substreams; int /*<<< orphan*/  dma_list; int /*<<< orphan*/  msrc_list; int /*<<< orphan*/  adc1_list; int /*<<< orphan*/  mixer_list; int /*<<< orphan*/  reg_lock; struct m3_dma* substreams; } ;
struct m3_dma {int opened; int /*<<< orphan*/ ** index_list; struct snd_pcm_substream* substream; scalar_t__ running; } ;
struct TYPE_2__ {struct m3_dma* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_m3_substream_open(struct snd_m3 *chip, struct snd_pcm_substream *subs)
{
	int i;
	struct m3_dma *s;

	spin_lock_irq(&chip->reg_lock);
	for (i = 0; i < chip->num_substreams; i++) {
		s = &chip->substreams[i];
		if (! s->opened)
			goto __found;
	}
	spin_unlock_irq(&chip->reg_lock);
	return -ENOMEM;
__found:
	s->opened = 1;
	s->running = 0;
	spin_unlock_irq(&chip->reg_lock);

	subs->runtime->private_data = s;
	s->substream = subs;

	/* set list owners */
	if (subs->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		s->index_list[0] = &chip->mixer_list;
	} else
		s->index_list[0] = &chip->adc1_list;
	s->index_list[1] = &chip->msrc_list;
	s->index_list[2] = &chip->dma_list;

	return 0;
}