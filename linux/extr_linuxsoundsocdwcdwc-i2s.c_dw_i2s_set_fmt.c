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
struct snd_soc_dai {int dummy; } ;
struct dw_i2s_dev {int capability; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DW_I2S_MASTER ; 
 int DW_I2S_SLAVE ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBM_CFS 130 
#define  SND_SOC_DAIFMT_CBS_CFM 129 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct dw_i2s_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int dw_i2s_set_fmt(struct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	struct dw_i2s_dev *dev = snd_soc_dai_get_drvdata(cpu_dai);
	int ret = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		if (dev->capability & DW_I2S_SLAVE)
			ret = 0;
		else
			ret = -EINVAL;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		if (dev->capability & DW_I2S_MASTER)
			ret = 0;
		else
			ret = -EINVAL;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
	case SND_SOC_DAIFMT_CBS_CFM:
		ret = -EINVAL;
		break;
	default:
		dev_dbg(dev->dev, "dwc : Invalid master/slave format\n");
		ret = -EINVAL;
		break;
	}
	return ret;
}