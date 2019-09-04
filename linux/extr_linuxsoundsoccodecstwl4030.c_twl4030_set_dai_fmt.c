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
typedef  int /*<<< orphan*/  u8 ;
struct twl4030_priv {scalar_t__ codec_powered; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
#define  SND_SOC_DAIFMT_DSP_A 129 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  TWL4030_AIF_FORMAT ; 
 int /*<<< orphan*/  TWL4030_AIF_FORMAT_CODEC ; 
 int /*<<< orphan*/  TWL4030_AIF_FORMAT_TDM ; 
 int /*<<< orphan*/  TWL4030_AIF_SLAVE_EN ; 
 int /*<<< orphan*/  TWL4030_CLK256FS_EN ; 
 int /*<<< orphan*/  TWL4030_REG_AUDIO_IF ; 
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  twl4030_codec_enable (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  twl4030_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 old_format, format;

	/* get format */
	old_format = twl4030_read(component, TWL4030_REG_AUDIO_IF);
	format = old_format;

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		format &= ~(TWL4030_AIF_SLAVE_EN);
		format &= ~(TWL4030_CLK256FS_EN);
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		format |= TWL4030_AIF_SLAVE_EN;
		format |= TWL4030_CLK256FS_EN;
		break;
	default:
		return -EINVAL;
	}

	/* interface format */
	format &= ~TWL4030_AIF_FORMAT;
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		format |= TWL4030_AIF_FORMAT_CODEC;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		format |= TWL4030_AIF_FORMAT_TDM;
		break;
	default:
		return -EINVAL;
	}

	if (format != old_format) {
		if (twl4030->codec_powered) {
			/*
			 * If the codec is powered, than we need to toggle the
			 * codec power.
			 */
			twl4030_codec_enable(component, 0);
			twl4030_write(component, TWL4030_REG_AUDIO_IF, format);
			twl4030_codec_enable(component, 1);
		} else {
			twl4030_write(component, TWL4030_REG_AUDIO_IF, format);
		}
	}

	return 0;
}