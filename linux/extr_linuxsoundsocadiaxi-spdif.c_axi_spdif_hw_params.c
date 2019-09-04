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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axi_spdif {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_SPDIF_CTRL_CLKDIV_MASK ; 
 unsigned int AXI_SPDIF_CTRL_CLKDIV_OFFSET ; 
 unsigned int AXI_SPDIF_FREQ_32000 ; 
 unsigned int AXI_SPDIF_FREQ_44100 ; 
 unsigned int AXI_SPDIF_FREQ_48000 ; 
 unsigned int AXI_SPDIF_FREQ_NA ; 
 int /*<<< orphan*/  AXI_SPDIF_REG_CTRL ; 
 int /*<<< orphan*/  AXI_SPDIF_REG_STAT ; 
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct axi_spdif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axi_spdif_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct axi_spdif *spdif = snd_soc_dai_get_drvdata(dai);
	unsigned int rate = params_rate(params);
	unsigned int clkdiv, stat;

	switch (params_rate(params)) {
	case 32000:
		stat = AXI_SPDIF_FREQ_32000;
		break;
	case 44100:
		stat = AXI_SPDIF_FREQ_44100;
		break;
	case 48000:
		stat = AXI_SPDIF_FREQ_48000;
		break;
	default:
		stat = AXI_SPDIF_FREQ_NA;
		break;
	}

	clkdiv = DIV_ROUND_CLOSEST(clk_get_rate(spdif->clk_ref),
			rate * 64 * 2) - 1;
	clkdiv <<= AXI_SPDIF_CTRL_CLKDIV_OFFSET;

	regmap_write(spdif->regmap, AXI_SPDIF_REG_STAT, stat);
	regmap_update_bits(spdif->regmap, AXI_SPDIF_REG_CTRL,
		AXI_SPDIF_CTRL_CLKDIV_MASK, clkdiv);

	return 0;
}