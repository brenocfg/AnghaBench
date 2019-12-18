#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int frame_fmt; } ;
struct TYPE_9__ {TYPE_3__ config; } ;
struct snd_sof_dai {TYPE_5__* dai_config; TYPE_4__ comp_dai; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct snd_interval {int min; int max; } ;
struct TYPE_7__ {int fsync_rate; int tdm_slots; } ;
struct TYPE_10__ {int type; TYPE_2__ ssp; } ;
struct TYPE_6__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S16_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S24_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
#define  SOF_DAI_INTEL_ALH 134 
#define  SOF_DAI_INTEL_DMIC 133 
#define  SOF_DAI_INTEL_HDA 132 
#define  SOF_DAI_INTEL_SSP 131 
#define  SOF_IPC_FRAME_S16_LE 130 
#define  SOF_IPC_FRAME_S24_4LE 129 
#define  SOF_IPC_FRAME_S32_LE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_set_format (struct snd_mask*,int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_sof_dai* snd_sof_find_dai (struct snd_sof_dev*,char*) ; 

__attribute__((used)) static int sof_pcm_dai_link_fixup(struct snd_soc_pcm_runtime *rtd,
				  struct snd_pcm_hw_params *params)
{
	struct snd_interval *rate = hw_param_interval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval *channels = hw_param_interval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(component);
	struct snd_sof_dai *dai =
		snd_sof_find_dai(sdev, (char *)rtd->dai_link->name);

	/* no topology exists for this BE, try a common configuration */
	if (!dai) {
		dev_warn(sdev->dev, "warning: no topology found for BE DAI %s config\n",
			 rtd->dai_link->name);

		/*  set 48k, stereo, 16bits by default */
		rate->min = 48000;
		rate->max = 48000;

		channels->min = 2;
		channels->max = 2;

		snd_mask_none(fmt);
		snd_mask_set_format(fmt, SNDRV_PCM_FORMAT_S16_LE);

		return 0;
	}

	/* read format from topology */
	snd_mask_none(fmt);

	switch (dai->comp_dai.config.frame_fmt) {
	case SOF_IPC_FRAME_S16_LE:
		snd_mask_set_format(fmt, SNDRV_PCM_FORMAT_S16_LE);
		break;
	case SOF_IPC_FRAME_S24_4LE:
		snd_mask_set_format(fmt, SNDRV_PCM_FORMAT_S24_LE);
		break;
	case SOF_IPC_FRAME_S32_LE:
		snd_mask_set_format(fmt, SNDRV_PCM_FORMAT_S32_LE);
		break;
	default:
		dev_err(sdev->dev, "error: No available DAI format!\n");
		return -EINVAL;
	}

	/* read rate and channels from topology */
	switch (dai->dai_config->type) {
	case SOF_DAI_INTEL_SSP:
		rate->min = dai->dai_config->ssp.fsync_rate;
		rate->max = dai->dai_config->ssp.fsync_rate;
		channels->min = dai->dai_config->ssp.tdm_slots;
		channels->max = dai->dai_config->ssp.tdm_slots;

		dev_dbg(sdev->dev,
			"rate_min: %d rate_max: %d\n", rate->min, rate->max);
		dev_dbg(sdev->dev,
			"channels_min: %d channels_max: %d\n",
			channels->min, channels->max);

		break;
	case SOF_DAI_INTEL_DMIC:
		/* DMIC only supports 16 or 32 bit formats */
		if (dai->comp_dai.config.frame_fmt == SOF_IPC_FRAME_S24_4LE) {
			dev_err(sdev->dev,
				"error: invalid fmt %d for DAI type %d\n",
				dai->comp_dai.config.frame_fmt,
				dai->dai_config->type);
		}
		break;
	case SOF_DAI_INTEL_HDA:
		/* do nothing for HDA dai_link */
		break;
	case SOF_DAI_INTEL_ALH:
		/* do nothing for ALH dai_link */
		break;
	default:
		dev_err(sdev->dev, "error: invalid DAI type %d\n",
			dai->dai_config->type);
		break;
	}

	return 0;
}