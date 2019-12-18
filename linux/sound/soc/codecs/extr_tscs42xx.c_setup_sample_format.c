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
 int /*<<< orphan*/  RM_AIC1_WL ; 
 unsigned int RV_AIC1_WL_16 ; 
 unsigned int RV_AIC1_WL_20 ; 
 unsigned int RV_AIC1_WL_24 ; 
 unsigned int RV_AIC1_WL_32 ; 
 int /*<<< orphan*/  R_AIC1 ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int setup_sample_format(struct snd_soc_component *component,
		snd_pcm_format_t format)
{
	unsigned int width;
	int ret;

	switch (format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		width = RV_AIC1_WL_16;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		width = RV_AIC1_WL_20;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		width = RV_AIC1_WL_24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		width = RV_AIC1_WL_32;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported format width (%d)\n", ret);
		return ret;
	}
	ret = snd_soc_component_update_bits(component,
			R_AIC1, RM_AIC1_WL, width);
	if (ret < 0) {
		dev_err(component->dev,
				"Failed to set sample width (%d)\n", ret);
		return ret;
	}

	return 0;
}