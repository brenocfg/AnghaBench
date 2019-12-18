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
struct snd_pcm {int /*<<< orphan*/  private_free; struct snd_emu8000* private_data; } ;
struct snd_emu8000 {struct snd_pcm* pcm; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  emu8k_pcm_ops ; 
 int /*<<< orphan*/  snd_device_register (struct snd_card*,struct snd_pcm*) ; 
 int /*<<< orphan*/  snd_emu8000_pcm_free ; 
 int snd_pcm_new (struct snd_card*,char*,int,int,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int snd_emu8000_pcm_new(struct snd_card *card, struct snd_emu8000 *emu, int index)
{
	struct snd_pcm *pcm;
	int err;

	if ((err = snd_pcm_new(card, "Emu8000 PCM", index, 1, 0, &pcm)) < 0)
		return err;
	pcm->private_data = emu;
	pcm->private_free = snd_emu8000_pcm_free;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &emu8k_pcm_ops);
	emu->pcm = pcm;

	snd_device_register(card, pcm);

	return 0;
}