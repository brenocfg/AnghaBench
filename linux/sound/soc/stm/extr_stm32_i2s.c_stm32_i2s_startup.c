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
struct stm32_i2s_data {int fmt; int /*<<< orphan*/  regmap; int /*<<< orphan*/  i2sclk; int /*<<< orphan*/  irq_lock; struct snd_pcm_substream* substream; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2S_IFCR_MASK ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int SND_SOC_DAIFMT_DSP_A ; 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
 int /*<<< orphan*/  STM32_I2S_IFCR_REG ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct stm32_i2s_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int stm32_i2s_startup(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *cpu_dai)
{
	struct stm32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&i2s->irq_lock, flags);
	i2s->substream = substream;
	spin_unlock_irqrestore(&i2s->irq_lock, flags);

	if ((i2s->fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_DSP_A)
		snd_pcm_hw_constraint_single(substream->runtime,
					     SNDRV_PCM_HW_PARAM_CHANNELS, 2);

	ret = clk_prepare_enable(i2s->i2sclk);
	if (ret < 0) {
		dev_err(cpu_dai->dev, "Failed to enable clock: %d\n", ret);
		return ret;
	}

	return regmap_write_bits(i2s->regmap, STM32_I2S_IFCR_REG,
				 I2S_IFCR_MASK, I2S_IFCR_MASK);
}