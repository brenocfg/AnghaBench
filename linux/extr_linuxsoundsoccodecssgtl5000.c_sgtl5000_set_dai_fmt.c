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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct sgtl5000_priv {int master; unsigned int fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SGTL5000_CHIP_I2S_CTRL ; 
 int SGTL5000_I2S_LRALIGN ; 
 int SGTL5000_I2S_LRPOL ; 
 int SGTL5000_I2S_MASTER ; 
 int SGTL5000_I2S_MODE_I2S_LJ ; 
 int SGTL5000_I2S_MODE_PCM ; 
 int SGTL5000_I2S_MODE_RJ ; 
 int SGTL5000_I2S_MODE_SHIFT ; 
 int SGTL5000_I2S_SCLK_INV ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
#define  SND_SOC_DAIFMT_DSP_A 134 
#define  SND_SOC_DAIFMT_DSP_B 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 struct sgtl5000_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sgtl5000_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct sgtl5000_priv *sgtl5000 = snd_soc_component_get_drvdata(component);
	u16 i2sctl = 0;

	sgtl5000->master = 0;
	/*
	 * i2s clock and frame master setting.
	 * ONLY support:
	 *  - clock and frame slave,
	 *  - clock and frame master
	 */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		i2sctl |= SGTL5000_I2S_MASTER;
		sgtl5000->master = 1;
		break;
	default:
		return -EINVAL;
	}

	/* setting i2s data format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		i2sctl |= SGTL5000_I2S_MODE_PCM << SGTL5000_I2S_MODE_SHIFT;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		i2sctl |= SGTL5000_I2S_MODE_PCM << SGTL5000_I2S_MODE_SHIFT;
		i2sctl |= SGTL5000_I2S_LRALIGN;
		break;
	case SND_SOC_DAIFMT_I2S:
		i2sctl |= SGTL5000_I2S_MODE_I2S_LJ << SGTL5000_I2S_MODE_SHIFT;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		i2sctl |= SGTL5000_I2S_MODE_RJ << SGTL5000_I2S_MODE_SHIFT;
		i2sctl |= SGTL5000_I2S_LRPOL;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		i2sctl |= SGTL5000_I2S_MODE_I2S_LJ << SGTL5000_I2S_MODE_SHIFT;
		i2sctl |= SGTL5000_I2S_LRALIGN;
		break;
	default:
		return -EINVAL;
	}

	sgtl5000->fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	/* Clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		i2sctl |= SGTL5000_I2S_SCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, SGTL5000_CHIP_I2S_CTRL, i2sctl);

	return 0;
}