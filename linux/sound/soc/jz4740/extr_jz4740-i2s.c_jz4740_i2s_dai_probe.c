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
typedef  int uint32_t ;
struct snd_soc_dai {int dummy; } ;
struct jz4740_i2s {scalar_t__ version; int /*<<< orphan*/  capture_dma_data; int /*<<< orphan*/  playback_dma_data; int /*<<< orphan*/  clk_aic; } ;

/* Variables and functions */
 int JZ4780_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET ; 
 int JZ4780_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET ; 
 int JZ_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET ; 
 int JZ_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET ; 
 int JZ_AIC_CONF_I2S ; 
 int JZ_AIC_CONF_INTERNAL_CODEC ; 
 int JZ_AIC_CONF_OVERFLOW_PLAY_LAST ; 
 int JZ_AIC_CONF_RESET ; 
 scalar_t__ JZ_I2S_JZ4780 ; 
 int /*<<< orphan*/  JZ_REG_AIC_CONF ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_i2c_init_pcm_config (struct jz4740_i2s*) ; 
 int /*<<< orphan*/  jz4740_i2s_write (struct jz4740_i2s*,int /*<<< orphan*/ ,int) ; 
 struct jz4740_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4740_i2s_dai_probe(struct snd_soc_dai *dai)
{
	struct jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	uint32_t conf;
	int ret;

	ret = clk_prepare_enable(i2s->clk_aic);
	if (ret)
		return ret;

	jz4740_i2c_init_pcm_config(i2s);
	snd_soc_dai_init_dma_data(dai, &i2s->playback_dma_data,
		&i2s->capture_dma_data);

	if (i2s->version >= JZ_I2S_JZ4780) {
		conf = (7 << JZ4780_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET) |
			(8 << JZ4780_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET) |
			JZ_AIC_CONF_OVERFLOW_PLAY_LAST |
			JZ_AIC_CONF_I2S |
			JZ_AIC_CONF_INTERNAL_CODEC;
	} else {
		conf = (7 << JZ_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET) |
			(8 << JZ_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET) |
			JZ_AIC_CONF_OVERFLOW_PLAY_LAST |
			JZ_AIC_CONF_I2S |
			JZ_AIC_CONF_INTERNAL_CODEC;
	}

	jz4740_i2s_write(i2s, JZ_REG_AIC_CONF, JZ_AIC_CONF_RESET);
	jz4740_i2s_write(i2s, JZ_REG_AIC_CONF, conf);

	return 0;
}