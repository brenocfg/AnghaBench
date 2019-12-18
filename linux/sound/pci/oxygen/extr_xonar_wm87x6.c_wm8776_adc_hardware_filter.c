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
struct snd_pcm_hardware {int rates; int rate_max; } ;

/* Variables and functions */
 unsigned int PCM_A ; 
 int SNDRV_PCM_RATE_32000 ; 
 int SNDRV_PCM_RATE_44100 ; 
 int SNDRV_PCM_RATE_48000 ; 
 int SNDRV_PCM_RATE_64000 ; 
 int SNDRV_PCM_RATE_88200 ; 
 int SNDRV_PCM_RATE_96000 ; 

__attribute__((used)) static void wm8776_adc_hardware_filter(unsigned int channel,
				       struct snd_pcm_hardware *hardware)
{
	if (channel == PCM_A) {
		hardware->rates = SNDRV_PCM_RATE_32000 |
				  SNDRV_PCM_RATE_44100 |
				  SNDRV_PCM_RATE_48000 |
				  SNDRV_PCM_RATE_64000 |
				  SNDRV_PCM_RATE_88200 |
				  SNDRV_PCM_RATE_96000;
		hardware->rate_max = 96000;
	}
}