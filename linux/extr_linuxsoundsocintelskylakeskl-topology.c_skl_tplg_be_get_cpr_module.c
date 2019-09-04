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
struct skl_module_cfg {int dummy; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 struct skl_module_cfg* skl_get_mconfig_cap_cpr (struct snd_soc_dai*,struct snd_soc_dapm_widget*) ; 
 struct skl_module_cfg* skl_get_mconfig_pb_cpr (struct snd_soc_dai*,struct snd_soc_dapm_widget*) ; 

struct skl_module_cfg *
skl_tplg_be_get_cpr_module(struct snd_soc_dai *dai, int stream)
{
	struct snd_soc_dapm_widget *w;
	struct skl_module_cfg *mconfig;

	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		w = dai->playback_widget;
		mconfig = skl_get_mconfig_pb_cpr(dai, w);
	} else {
		w = dai->capture_widget;
		mconfig = skl_get_mconfig_cap_cpr(dai, w);
	}
	return mconfig;
}