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
struct snd_ymfpci_pcm {int /*<<< orphan*/ ** voices; } ;
struct snd_ymfpci {int dummy; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_ymfpci_pcm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ymfpci_irq_wait (struct snd_ymfpci*) ; 
 int /*<<< orphan*/  snd_ymfpci_voice_free (struct snd_ymfpci*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_playback_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ymfpci_pcm *ypcm;
	
	if (runtime->private_data == NULL)
		return 0;
	ypcm = runtime->private_data;

	/* wait, until the PCI operations are not finished */
	snd_ymfpci_irq_wait(chip);
	snd_pcm_lib_free_pages(substream);
	if (ypcm->voices[1]) {
		snd_ymfpci_voice_free(chip, ypcm->voices[1]);
		ypcm->voices[1] = NULL;
	}
	if (ypcm->voices[0]) {
		snd_ymfpci_voice_free(chip, ypcm->voices[0]);
		ypcm->voices[0] = NULL;
	}
	return 0;
}