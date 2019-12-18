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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct emu10k1x_pcm* private_data; } ;
struct emu10k1x_pcm {TYPE_1__* voice; } ;
struct TYPE_2__ {int /*<<< orphan*/ * epcm; scalar_t__ use; } ;

/* Variables and functions */
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1x_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct emu10k1x_pcm *epcm;

	if (runtime->private_data == NULL)
		return 0;
	
	epcm = runtime->private_data;

	if (epcm->voice) {
		epcm->voice->use = 0;
		epcm->voice->epcm = NULL;
		epcm->voice = NULL;
	}

	return snd_pcm_lib_free_pages(substream);
}