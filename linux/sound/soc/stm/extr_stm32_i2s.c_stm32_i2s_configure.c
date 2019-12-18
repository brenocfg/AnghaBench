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
typedef  int u32 ;
struct stm32_i2s_data {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2S_CFG1_FTHVL_MASK ; 
 int I2S_CFG1_FTHVL_SET (unsigned int) ; 
 int I2S_CGFR_CHLEN ; 
 int I2S_CGFR_DATLEN_MASK ; 
 int I2S_CGFR_DATLEN_SET (int /*<<< orphan*/ ) ; 
 int I2S_CGFR_FIXCH ; 
 int I2S_CGFR_I2SCFG_MASK ; 
 int I2S_CGFR_I2SCFG_SET (int /*<<< orphan*/ ) ; 
 int I2S_FIFO_TH_ONE_QUARTER ; 
 int /*<<< orphan*/  I2S_I2SMOD_DATLEN_16 ; 
 int /*<<< orphan*/  I2S_I2SMOD_DATLEN_32 ; 
 int /*<<< orphan*/  I2S_I2SMOD_FD_MASTER ; 
 int /*<<< orphan*/  I2S_I2SMOD_FD_SLAVE ; 
 int /*<<< orphan*/  STM32_I2S_CFG1_REG ; 
 int /*<<< orphan*/  STM32_I2S_CGFR_REG ; 
 int STM32_I2S_FIFO_SIZE ; 
 scalar_t__ STM32_I2S_IS_SLAVE (struct stm32_i2s_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_i2s_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_i2s_configure(struct snd_soc_dai *cpu_dai,
			       struct snd_pcm_hw_params *params,
			       struct snd_pcm_substream *substream)
{
	struct stm32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	int format = params_width(params);
	u32 cfgr, cfgr_mask, cfg1;
	unsigned int fthlv;
	int ret;

	switch (format) {
	case 16:
		cfgr = I2S_CGFR_DATLEN_SET(I2S_I2SMOD_DATLEN_16);
		cfgr_mask = I2S_CGFR_DATLEN_MASK | I2S_CGFR_CHLEN;
		break;
	case 32:
		cfgr = I2S_CGFR_DATLEN_SET(I2S_I2SMOD_DATLEN_32) |
					   I2S_CGFR_CHLEN;
		cfgr_mask = I2S_CGFR_DATLEN_MASK | I2S_CGFR_CHLEN;
		break;
	default:
		dev_err(cpu_dai->dev, "Unexpected format %d", format);
		return -EINVAL;
	}

	if (STM32_I2S_IS_SLAVE(i2s)) {
		cfgr |= I2S_CGFR_I2SCFG_SET(I2S_I2SMOD_FD_SLAVE);

		/* As data length is either 16 or 32 bits, fixch always set */
		cfgr |= I2S_CGFR_FIXCH;
		cfgr_mask |= I2S_CGFR_FIXCH;
	} else {
		cfgr |= I2S_CGFR_I2SCFG_SET(I2S_I2SMOD_FD_MASTER);
	}
	cfgr_mask |= I2S_CGFR_I2SCFG_MASK;

	ret = regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				 cfgr_mask, cfgr);
	if (ret < 0)
		return ret;

	fthlv = STM32_I2S_FIFO_SIZE * I2S_FIFO_TH_ONE_QUARTER / 4;
	cfg1 = I2S_CFG1_FTHVL_SET(fthlv - 1);

	return regmap_update_bits(i2s->regmap, STM32_I2S_CFG1_REG,
				  I2S_CFG1_FTHVL_MASK, cfg1);
}