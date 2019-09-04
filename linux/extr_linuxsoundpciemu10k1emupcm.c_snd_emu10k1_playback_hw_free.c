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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm {scalar_t__ start_addr; int /*<<< orphan*/ * memblk; int /*<<< orphan*/ ** voices; int /*<<< orphan*/  emu; int /*<<< orphan*/ * extra; } ;
struct snd_emu10k1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_emu10k1_free_pages (struct snd_emu10k1*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_playback_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm;

	if (runtime->private_data == NULL)
		return 0;
	epcm = runtime->private_data;
	if (epcm->extra) {
		snd_emu10k1_voice_free(epcm->emu, epcm->extra);
		epcm->extra = NULL;
	}
	if (epcm->voices[1]) {
		snd_emu10k1_voice_free(epcm->emu, epcm->voices[1]);
		epcm->voices[1] = NULL;
	}
	if (epcm->voices[0]) {
		snd_emu10k1_voice_free(epcm->emu, epcm->voices[0]);
		epcm->voices[0] = NULL;
	}
	if (epcm->memblk) {
		snd_emu10k1_free_pages(emu, epcm->memblk);
		epcm->memblk = NULL;
		epcm->start_addr = 0;
	}
	snd_pcm_lib_free_pages(substream);
	return 0;
}