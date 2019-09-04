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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCLK_TO_FS_MSK ; 
 int /*<<< orphan*/  CAP_FREQ_RANGE_MSK ; 
 int EINVAL ; 
 int /*<<< orphan*/  PDATA_LEN_MSK ; 
 int /*<<< orphan*/  PLAY_FREQ_RANGE_MSK ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  STA529_MISC ; 
 int /*<<< orphan*/  STA529_P2SCFG1 ; 
 int /*<<< orphan*/  STA529_S2PCFG1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sta529_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	int pdata, play_freq_val, record_freq_val;
	int bclk_to_fs_ratio;

	switch (params_width(params)) {
	case 16:
		pdata = 1;
		bclk_to_fs_ratio = 0;
		break;
	case 24:
		pdata = 2;
		bclk_to_fs_ratio = 1;
		break;
	case 32:
		pdata = 3;
		bclk_to_fs_ratio = 2;
		break;
	default:
		dev_err(component->dev, "Unsupported format\n");
		return -EINVAL;
	}

	switch (params_rate(params)) {
	case 8000:
	case 11025:
		play_freq_val = 0;
		record_freq_val = 2;
		break;
	case 16000:
	case 22050:
		play_freq_val = 1;
		record_freq_val = 0;
		break;

	case 32000:
	case 44100:
	case 48000:
		play_freq_val = 2;
		record_freq_val = 0;
		break;
	default:
		dev_err(component->dev, "Unsupported rate\n");
		return -EINVAL;
	}

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		snd_soc_component_update_bits(component, STA529_S2PCFG1, PDATA_LEN_MSK,
				pdata << 6);
		snd_soc_component_update_bits(component, STA529_S2PCFG1, BCLK_TO_FS_MSK,
				bclk_to_fs_ratio << 4);
		snd_soc_component_update_bits(component, STA529_MISC, PLAY_FREQ_RANGE_MSK,
				play_freq_val << 4);
	} else {
		snd_soc_component_update_bits(component, STA529_P2SCFG1, PDATA_LEN_MSK,
				pdata << 6);
		snd_soc_component_update_bits(component, STA529_P2SCFG1, BCLK_TO_FS_MSK,
				bclk_to_fs_ratio << 4);
		snd_soc_component_update_bits(component, STA529_MISC, CAP_FREQ_RANGE_MSK,
				record_freq_val << 2);
	}

	return 0;
}