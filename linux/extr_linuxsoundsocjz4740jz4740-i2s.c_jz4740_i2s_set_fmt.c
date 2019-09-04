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
struct jz4740_i2s {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int JZ_AIC_CONF_BIT_CLK_MASTER ; 
 int JZ_AIC_CONF_SYNC_CLK_MASTER ; 
 int JZ_AIC_I2S_FMT_ENABLE_SYS_CLK ; 
 int JZ_AIC_I2S_FMT_MSB ; 
 int /*<<< orphan*/  JZ_REG_AIC_CONF ; 
 int /*<<< orphan*/  JZ_REG_AIC_I2S_FMT ; 
#define  SND_SOC_DAIFMT_CBM_CFM 134 
#define  SND_SOC_DAIFMT_CBM_CFS 133 
#define  SND_SOC_DAIFMT_CBS_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_MSB 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int jz4740_i2s_read (struct jz4740_i2s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_i2s_write (struct jz4740_i2s*,int /*<<< orphan*/ ,int) ; 
 struct jz4740_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int jz4740_i2s_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	uint32_t format = 0;
	uint32_t conf;

	conf = jz4740_i2s_read(i2s, JZ_REG_AIC_CONF);

	conf &= ~(JZ_AIC_CONF_BIT_CLK_MASTER | JZ_AIC_CONF_SYNC_CLK_MASTER);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		conf |= JZ_AIC_CONF_BIT_CLK_MASTER | JZ_AIC_CONF_SYNC_CLK_MASTER;
		format |= JZ_AIC_I2S_FMT_ENABLE_SYS_CLK;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		conf |= JZ_AIC_CONF_SYNC_CLK_MASTER;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		conf |= JZ_AIC_CONF_BIT_CLK_MASTER;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_MSB:
		format |= JZ_AIC_I2S_FMT_MSB;
		break;
	case SND_SOC_DAIFMT_I2S:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	default:
		return -EINVAL;
	}

	jz4740_i2s_write(i2s, JZ_REG_AIC_CONF, conf);
	jz4740_i2s_write(i2s, JZ_REG_AIC_I2S_FMT, format);

	return 0;
}