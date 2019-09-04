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
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_soc_dai {struct snd_soc_dapm_widget* capture_widget; struct snd_soc_dapm_widget* playback_widget; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static inline struct snd_soc_dapm_widget *
	dai_get_widget(struct snd_soc_dai *dai, int stream)
{
	if (stream == SNDRV_PCM_STREAM_PLAYBACK)
		return dai->playback_widget;
	else
		return dai->capture_widget;
}