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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RM_AIC1_MS ; 
 int /*<<< orphan*/  RV_AIC1_MS_MASTER ; 
 int /*<<< orphan*/  R_AIC1 ; 
#define  SND_SOC_DAIFMT_CBM_CFM 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tscs42xx_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	int ret;

	/* Slave mode not supported since it needs always-on frame clock */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		ret = snd_soc_component_update_bits(component,
				R_AIC1, RM_AIC1_MS, RV_AIC1_MS_MASTER);
		if (ret < 0) {
			dev_err(component->dev,
				"Failed to set codec DAI master (%d)\n", ret);
			return ret;
		}
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Unsupported format (%d)\n", ret);
		return ret;
	}

	return 0;
}