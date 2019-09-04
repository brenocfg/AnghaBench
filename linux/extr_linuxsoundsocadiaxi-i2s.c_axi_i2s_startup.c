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
typedef  int /*<<< orphan*/  uint32_t ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
struct axi_i2s {int /*<<< orphan*/  clk_ref; int /*<<< orphan*/  rate_constraints; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_I2S_REG_RESET ; 
 int /*<<< orphan*/  AXI_I2S_RESET_RX_FIFO ; 
 int /*<<< orphan*/  AXI_I2S_RESET_TX_FIFO ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_ratnums (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct axi_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axi_i2s_startup(struct snd_pcm_substream *substream,
	struct snd_soc_dai *dai)
{
	struct axi_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	uint32_t mask;
	int ret;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mask = AXI_I2S_RESET_RX_FIFO;
	else
		mask = AXI_I2S_RESET_TX_FIFO;

	regmap_write(i2s->regmap, AXI_I2S_REG_RESET, mask);

	ret = snd_pcm_hw_constraint_ratnums(substream->runtime, 0,
			   SNDRV_PCM_HW_PARAM_RATE,
			   &i2s->rate_constraints);
	if (ret)
		return ret;

	return clk_prepare_enable(i2s->clk_ref);
}