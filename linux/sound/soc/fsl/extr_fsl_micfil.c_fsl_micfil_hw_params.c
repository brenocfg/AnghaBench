#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {unsigned int maxburst; } ;
struct fsl_micfil {TYPE_2__ dma_params_rx; int /*<<< orphan*/  regmap; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int MICFIL_CTRL1_PDMIEN_MASK ; 
 unsigned int MICFIL_DMA_MAXBURST_RX ; 
 int /*<<< orphan*/  REG_MICFIL_CTRL1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int fsl_set_clock_params (struct device*,unsigned int) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct fsl_micfil* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_micfil_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);
	unsigned int channels = params_channels(params);
	unsigned int rate = params_rate(params);
	struct device *dev = &micfil->pdev->dev;
	int ret;

	/* 1. Disable the module */
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
				 MICFIL_CTRL1_PDMIEN_MASK, 0);
	if (ret) {
		dev_err(dev, "failed to disable the module\n");
		return ret;
	}

	/* enable channels */
	ret = regmap_update_bits(micfil->regmap, REG_MICFIL_CTRL1,
				 0xFF, ((1 << channels) - 1));
	if (ret) {
		dev_err(dev, "failed to enable channels %d, reg 0x%X\n", ret,
			REG_MICFIL_CTRL1);
		return ret;
	}

	ret = fsl_set_clock_params(dev, rate);
	if (ret < 0) {
		dev_err(dev, "Failed to set clock parameters [%d]\n", ret);
		return ret;
	}

	micfil->dma_params_rx.maxburst = channels * MICFIL_DMA_MAXBURST_RX;

	return 0;
}