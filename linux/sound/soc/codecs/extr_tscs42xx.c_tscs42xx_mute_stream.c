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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int adc_mute (struct snd_soc_component*) ; 
 int adc_unmute (struct snd_soc_component*) ; 
 int dac_mute (struct snd_soc_component*) ; 
 int dac_unmute (struct snd_soc_component*) ; 

__attribute__((used)) static int tscs42xx_mute_stream(struct snd_soc_dai *dai, int mute, int stream)
{
	struct snd_soc_component *component = dai->component;
	int ret;

	if (mute)
		if (stream == SNDRV_PCM_STREAM_PLAYBACK)
			ret = dac_mute(component);
		else
			ret = adc_mute(component);
	else
		if (stream == SNDRV_PCM_STREAM_PLAYBACK)
			ret = dac_unmute(component);
		else
			ret = adc_unmute(component);

	return ret;
}