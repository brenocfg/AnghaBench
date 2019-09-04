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
struct skl_pipe_params {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int skl_tplg_be_set_sink_pipe_params (struct snd_soc_dai*,struct snd_soc_dapm_widget*,struct skl_pipe_params*) ; 
 int skl_tplg_be_set_src_pipe_params (struct snd_soc_dai*,struct snd_soc_dapm_widget*,struct skl_pipe_params*) ; 

int skl_tplg_be_update_params(struct snd_soc_dai *dai,
				struct skl_pipe_params *params)
{
	struct snd_soc_dapm_widget *w;

	if (params->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		w = dai->playback_widget;

		return skl_tplg_be_set_src_pipe_params(dai, w, params);

	} else {
		w = dai->capture_widget;

		return skl_tplg_be_set_sink_pipe_params(dai, w, params);
	}

	return 0;
}