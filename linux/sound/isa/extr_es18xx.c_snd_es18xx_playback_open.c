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
struct snd_pcm_substream {int number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct snd_es18xx {int caps; struct snd_pcm_substream* playback_b_substream; TYPE_2__* capture_a_substream; struct snd_pcm_substream* playback_a_substream; } ;
struct TYPE_4__ {TYPE_1__* runtime; } ;
struct TYPE_3__ {int channels; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ES18XX_DUPLEX_MONO ; 
 int ES18XX_NEW_RATE ; 
 int ES18XX_PCM2 ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  new_hw_constraints_clocks ; 
 int /*<<< orphan*/  old_hw_constraints_clocks ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  snd_es18xx_playback ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_ratnums (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_es18xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es18xx_playback_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
        struct snd_es18xx *chip = snd_pcm_substream_chip(substream);

	if (substream->number == 0 && (chip->caps & ES18XX_PCM2)) {
		if ((chip->caps & ES18XX_DUPLEX_MONO) &&
		    chip->capture_a_substream && 
		    chip->capture_a_substream->runtime->channels != 1)
			return -EAGAIN;
		chip->playback_a_substream = substream;
	} else if (substream->number <= 1) {
		if (chip->capture_a_substream)
			return -EAGAIN;
		chip->playback_b_substream = substream;
	} else {
		snd_BUG();
		return -EINVAL;
	}
	substream->runtime->hw = snd_es18xx_playback;
	snd_pcm_hw_constraint_ratnums(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				      (chip->caps & ES18XX_NEW_RATE) ? &new_hw_constraints_clocks : &old_hw_constraints_clocks);
        return 0;
}