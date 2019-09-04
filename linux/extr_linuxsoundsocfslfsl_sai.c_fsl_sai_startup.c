#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
struct fsl_sai {int /*<<< orphan*/  regmap; int /*<<< orphan*/  bus_clk; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_SAI_CR3_TRCE ; 
 int /*<<< orphan*/  FSL_SAI_xCR3 (int) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  fsl_sai_rate_constraints ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fsl_sai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_sai_startup(struct snd_pcm_substream *substream,
		struct snd_soc_dai *cpu_dai)
{
	struct fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	struct device *dev = &sai->pdev->dev;
	int ret;

	ret = clk_prepare_enable(sai->bus_clk);
	if (ret) {
		dev_err(dev, "failed to enable bus clock: %d\n", ret);
		return ret;
	}

	regmap_update_bits(sai->regmap, FSL_SAI_xCR3(tx), FSL_SAI_CR3_TRCE,
			   FSL_SAI_CR3_TRCE);

	ret = snd_pcm_hw_constraint_list(substream->runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, &fsl_sai_rate_constraints);

	return ret;
}