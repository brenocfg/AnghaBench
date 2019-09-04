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
struct snd_pcm_substream {size_t number; struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int period_bytes_max; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; } ;
struct snd_pcm_runtime {TYPE_2__ hw; } ;
struct snd_emu10k1_fx8010_pcm {int buffer_size; scalar_t__ valid; int opened; int /*<<< orphan*/  channels; } ;
struct TYPE_3__ {struct snd_emu10k1_fx8010_pcm* pcm; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; TYPE_1__ fx8010; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ snd_emu10k1_fx8010_playback ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu10k1_fx8010_playback_open(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];

	runtime->hw = snd_emu10k1_fx8010_playback;
	runtime->hw.channels_min = runtime->hw.channels_max = pcm->channels;
	runtime->hw.period_bytes_max = (pcm->buffer_size * 2) / 2;
	spin_lock_irq(&emu->reg_lock);
	if (pcm->valid == 0) {
		spin_unlock_irq(&emu->reg_lock);
		return -ENODEV;
	}
	pcm->opened = 1;
	spin_unlock_irq(&emu->reg_lock);
	return 0;
}