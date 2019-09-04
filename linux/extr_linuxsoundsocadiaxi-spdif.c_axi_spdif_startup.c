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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct axi_spdif {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_ref; int /*<<< orphan*/  rate_constraints; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_SPDIF_CTRL_TXEN ; 
 int /*<<< orphan*/  AXI_SPDIF_REG_CTRL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_ratnums (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct axi_spdif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axi_spdif_startup(struct snd_pcm_substream *substream,
	struct snd_soc_dai *dai)
{
	struct axi_spdif *spdif = snd_soc_dai_get_drvdata(dai);
	int ret;

	ret = snd_pcm_hw_constraint_ratnums(substream->runtime, 0,
			   SNDRV_PCM_HW_PARAM_RATE,
			   &spdif->rate_constraints);
	if (ret)
		return ret;

	ret = clk_prepare_enable(spdif->clk_ref);
	if (ret)
		return ret;

	regmap_update_bits(spdif->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_TXEN, AXI_SPDIF_CTRL_TXEN);

	return 0;
}