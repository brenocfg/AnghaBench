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
struct snd_pcm_substream {scalar_t__ number; } ;
struct snd_es18xx {int caps; } ;

/* Variables and functions */
 int ES18XX_PCM2 ; 
 int snd_es18xx_playback1_trigger (struct snd_es18xx*,struct snd_pcm_substream*,int) ; 
 int snd_es18xx_playback2_trigger (struct snd_es18xx*,struct snd_pcm_substream*,int) ; 
 struct snd_es18xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es18xx_playback_trigger(struct snd_pcm_substream *substream,
				       int cmd)
{
        struct snd_es18xx *chip = snd_pcm_substream_chip(substream);
	if (substream->number == 0 && (chip->caps & ES18XX_PCM2))
		return snd_es18xx_playback1_trigger(chip, substream, cmd);
	else
		return snd_es18xx_playback2_trigger(chip, substream, cmd);
}