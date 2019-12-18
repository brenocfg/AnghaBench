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
struct wl1273_priv {int mode; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; int /*<<< orphan*/  runtime; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  WL1273_MODE_BT 130 
#define  WL1273_MODE_FM_RX 129 
#define  WL1273_MODE_FM_TX 128 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct wl1273_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wl1273_startup(struct snd_pcm_substream *substream,
			  struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	switch (wl1273->mode) {
	case WL1273_MODE_BT:
		snd_pcm_hw_constraint_single(substream->runtime,
					     SNDRV_PCM_HW_PARAM_RATE, 8000);
		snd_pcm_hw_constraint_single(substream->runtime,
					     SNDRV_PCM_HW_PARAM_CHANNELS, 1);
		break;
	case WL1273_MODE_FM_RX:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			pr_err("Cannot play in RX mode.\n");
			return -EINVAL;
		}
		break;
	case WL1273_MODE_FM_TX:
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
			pr_err("Cannot capture in TX mode.\n");
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
		break;
	}

	return 0;
}