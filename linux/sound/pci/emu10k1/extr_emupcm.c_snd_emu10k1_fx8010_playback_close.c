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
struct snd_pcm_substream {size_t number; } ;
struct snd_emu10k1_fx8010_pcm {scalar_t__ opened; } ;
struct TYPE_2__ {struct snd_emu10k1_fx8010_pcm* pcm; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; TYPE_1__ fx8010; } ;

/* Variables and functions */
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu10k1_fx8010_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_emu10k1_fx8010_pcm *pcm = &emu->fx8010.pcm[substream->number];

	spin_lock_irq(&emu->reg_lock);
	pcm->opened = 0;
	spin_unlock_irq(&emu->reg_lock);
	return 0;
}