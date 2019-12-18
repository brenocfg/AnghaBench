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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INNO_R02 ; 
 int INNO_R02_LRCP_MSK ; 
 unsigned int INNO_R02_LRCP_NORMAL ; 
 unsigned int INNO_R02_VWL_16BIT ; 
 unsigned int INNO_R02_VWL_20BIT ; 
 unsigned int INNO_R02_VWL_24BIT ; 
 unsigned int INNO_R02_VWL_32BIT ; 
 int INNO_R02_VWL_MSK ; 
 int /*<<< orphan*/  INNO_R03 ; 
 int INNO_R03_DACR_MSK ; 
 unsigned int INNO_R03_DACR_WORK ; 
 unsigned int INNO_R03_FWL_32BIT ; 
 int INNO_R03_FWL_MSK ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int rk3036_codec_dai_hw_params(struct snd_pcm_substream *substream,
				      struct snd_pcm_hw_params *hw_params,
				      struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	unsigned int reg02_val = 0, reg03_val = 0;

	switch (params_format(hw_params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		reg02_val |= INNO_R02_VWL_16BIT;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		reg02_val |= INNO_R02_VWL_20BIT;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		reg02_val |= INNO_R02_VWL_24BIT;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		reg02_val |= INNO_R02_VWL_32BIT;
		break;
	default:
		return -EINVAL;
	}

	reg02_val |= INNO_R02_LRCP_NORMAL;
	reg03_val |= INNO_R03_FWL_32BIT | INNO_R03_DACR_WORK;

	snd_soc_component_update_bits(component, INNO_R02, INNO_R02_LRCP_MSK |
			    INNO_R02_VWL_MSK, reg02_val);
	snd_soc_component_update_bits(component, INNO_R03, INNO_R03_DACR_MSK |
			    INNO_R03_FWL_MSK, reg03_val);
	return 0;
}