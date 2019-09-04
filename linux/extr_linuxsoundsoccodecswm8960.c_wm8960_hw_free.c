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
struct wm8960_priv {int* is_stream_in_use; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct wm8960_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8960_hw_free(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8960_priv *wm8960 = snd_soc_component_get_drvdata(component);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	wm8960->is_stream_in_use[tx] = false;

	return 0;
}