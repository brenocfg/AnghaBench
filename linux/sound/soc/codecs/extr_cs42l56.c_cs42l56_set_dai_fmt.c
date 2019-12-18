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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct cs42l56_private {int /*<<< orphan*/  iface_inv; int /*<<< orphan*/  iface_fmt; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42L56_CLKCTL_1 ; 
 int /*<<< orphan*/  CS42L56_DIG_FMT_I2S ; 
 int /*<<< orphan*/  CS42L56_DIG_FMT_LEFT_J ; 
 int /*<<< orphan*/  CS42L56_DIG_FMT_MASK ; 
 int /*<<< orphan*/  CS42L56_MASTER_MODE ; 
 int /*<<< orphan*/  CS42L56_MS_MODE_MASK ; 
 int /*<<< orphan*/  CS42L56_SCLK_INV ; 
 int /*<<< orphan*/  CS42L56_SCLK_INV_MASK ; 
 int /*<<< orphan*/  CS42L56_SERIAL_FMT ; 
 int /*<<< orphan*/  CS42L56_SLAVE_MODE ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 128 
 struct cs42l56_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs42l56_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs42l56_private *cs42l56 = snd_soc_component_get_drvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		cs42l56->iface = CS42L56_MASTER_MODE;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		cs42l56->iface = CS42L56_SLAVE_MODE;
		break;
	default:
		return -EINVAL;
	}

	 /* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cs42l56->iface_fmt = CS42L56_DIG_FMT_I2S;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		cs42l56->iface_fmt = CS42L56_DIG_FMT_LEFT_J;
		break;
	default:
		return -EINVAL;
	}

	/* sclk inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		cs42l56->iface_inv = 0;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		cs42l56->iface_inv = CS42L56_SCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, CS42L56_CLKCTL_1,
			    CS42L56_MS_MODE_MASK, cs42l56->iface);
	snd_soc_component_update_bits(component, CS42L56_SERIAL_FMT,
			    CS42L56_DIG_FMT_MASK, cs42l56->iface_fmt);
	snd_soc_component_update_bits(component, CS42L56_CLKCTL_1,
			    CS42L56_SCLK_INV_MASK, cs42l56->iface_inv);
	return 0;
}