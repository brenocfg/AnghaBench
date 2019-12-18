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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  int snd_pcm_format_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FM_I2SPCTL_WL ; 
 unsigned int FV_WL_16 ; 
 unsigned int FV_WL_20 ; 
 unsigned int FV_WL_24 ; 
 unsigned int FV_WL_32 ; 
 unsigned int R_I2SP1CTL ; 
 unsigned int R_I2SP2CTL ; 
 unsigned int R_I2SP3CTL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 135 
#define  SNDRV_PCM_FORMAT_S20_3LE 134 
#define  SNDRV_PCM_FORMAT_S24_3LE 133 
#define  SNDRV_PCM_FORMAT_S24_LE 132 
#define  SNDRV_PCM_FORMAT_S32_LE 131 
#define  TSCS454_DAI1_ID 130 
#define  TSCS454_DAI2_ID 129 
#define  TSCS454_DAI3_ID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int set_aif_sample_format(struct snd_soc_component *component,
		snd_pcm_format_t format,
		int aif_id)
{
	unsigned int reg;
	unsigned int width;
	int ret;

	switch (format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		width = FV_WL_16;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		width = FV_WL_20;
		break;
	case SNDRV_PCM_FORMAT_S24_3LE:
		width = FV_WL_24;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
	case SNDRV_PCM_FORMAT_S32_LE:
		width = FV_WL_32;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported format width (%d)\n", ret);
		return ret;
	}

	switch (aif_id) {
	case TSCS454_DAI1_ID:
		reg = R_I2SP1CTL;
		break;
	case TSCS454_DAI2_ID:
		reg = R_I2SP2CTL;
		break;
	case TSCS454_DAI3_ID:
		reg = R_I2SP3CTL;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "AIF ID not recognized (%d)\n", ret);
		return ret;
	}

	ret = snd_soc_component_update_bits(component,
			reg, FM_I2SPCTL_WL, width);
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to set sample width (%d)\n", ret);
		return ret;
	}

	return 0;
}