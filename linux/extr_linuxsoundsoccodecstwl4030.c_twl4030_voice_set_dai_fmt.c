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
typedef  scalar_t__ u8 ;
struct twl4030_priv {scalar_t__ codec_powered; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
#define  SND_SOC_DAIFMT_IB_NF 129 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 128 
 int /*<<< orphan*/  TWL4030_REG_VOICE_IF ; 
 scalar_t__ TWL4030_VIF_FORMAT ; 
 scalar_t__ TWL4030_VIF_SLAVE_EN ; 
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  twl4030_codec_enable (struct snd_soc_component*,int) ; 
 scalar_t__ twl4030_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_write (struct snd_soc_component*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int twl4030_voice_set_dai_fmt(struct snd_soc_dai *codec_dai,
				     unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 old_format, format;

	/* get format */
	old_format = twl4030_read(component, TWL4030_REG_VOICE_IF);
	format = old_format;

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		format &= ~(TWL4030_VIF_SLAVE_EN);
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		format |= TWL4030_VIF_SLAVE_EN;
		break;
	default:
		return -EINVAL;
	}

	/* clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
		format &= ~(TWL4030_VIF_FORMAT);
		break;
	case SND_SOC_DAIFMT_NB_IF:
		format |= TWL4030_VIF_FORMAT;
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
			twl4030_write(component, TWL4030_REG_VOICE_IF, format);
			twl4030_codec_enable(component, 1);
		} else {
			twl4030_write(component, TWL4030_REG_VOICE_IF, format);
		}
	}

	return 0;
}