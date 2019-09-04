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
struct axi_i2s {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk_ref; } ;

/* Variables and functions */
 int AXI_I2S_BITS_PER_FRAME ; 
 int /*<<< orphan*/  AXI_I2S_REG_CLK_CTRL ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct axi_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axi_i2s_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int bclk_div, word_size;
	unsigned int bclk_rate;

	bclk_rate = params_rate(params) * AXI_I2S_BITS_PER_FRAME;

	word_size = AXI_I2S_BITS_PER_FRAME / 2 - 1;
	bclk_div = DIV_ROUND_UP(clk_get_rate(i2s->clk_ref), bclk_rate) / 2 - 1;

	regmap_write(i2s->regmap, AXI_I2S_REG_CLK_CTRL, (word_size << 16) |
		bclk_div);

	return 0;
}