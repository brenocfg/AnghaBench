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
struct wm8580_priv {TYPE_1__* drvdata; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct TYPE_2__ {int num_dacs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int snd_pcm_hw_constraint_minmax (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct wm8580_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8580_playback_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8580_priv *wm8580 = snd_soc_component_get_drvdata(component);

	return snd_pcm_hw_constraint_minmax(substream->runtime,
		SNDRV_PCM_HW_PARAM_CHANNELS, 1, wm8580->drvdata->num_dacs * 2);
}