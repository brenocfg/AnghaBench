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
struct tfa9879_priv {int lsb_justified; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBS_CFS 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int TFA9879_I2S_SET_I2S_24 ; 
 int TFA9879_I2S_SET_LSB_J_24 ; 
 int /*<<< orphan*/  TFA9879_I2S_SET_MASK ; 
 int TFA9879_I2S_SET_MSB_J_24 ; 
 int TFA9879_I2S_SET_SHIFT ; 
 int TFA9879_SCK_POL_INVERSE ; 
 int /*<<< orphan*/  TFA9879_SCK_POL_MASK ; 
 int TFA9879_SCK_POL_NORMAL ; 
 int TFA9879_SCK_POL_SHIFT ; 
 int /*<<< orphan*/  TFA9879_SERIAL_INTERFACE_1 ; 
 struct tfa9879_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tfa9879_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct tfa9879_priv *tfa9879 = snd_soc_component_get_drvdata(component);
	int i2s_set;
	int sck_pol;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		sck_pol = TFA9879_SCK_POL_NORMAL;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		sck_pol = TFA9879_SCK_POL_INVERSE;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		tfa9879->lsb_justified = 0;
		i2s_set = TFA9879_I2S_SET_I2S_24;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		tfa9879->lsb_justified = 0;
		i2s_set = TFA9879_I2S_SET_MSB_J_24;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		tfa9879->lsb_justified = 1;
		i2s_set = TFA9879_I2S_SET_LSB_J_24;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, TFA9879_SERIAL_INTERFACE_1,
				      TFA9879_SCK_POL_MASK,
				      sck_pol << TFA9879_SCK_POL_SHIFT);
	snd_soc_component_update_bits(component, TFA9879_SERIAL_INTERFACE_1,
				      TFA9879_I2S_SET_MASK,
				      i2s_set << TFA9879_I2S_SET_SHIFT);
	return 0;
}