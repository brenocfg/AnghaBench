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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct rt5663_priv {int codec_ver; } ;

/* Variables and functions */
#define  CODEC_VER_0 129 
#define  CODEC_VER_1 128 
 int EINVAL ; 
 unsigned int RT5663_TDM_1 ; 
 unsigned int RT5663_TDM_2 ; 
 unsigned int RT5663_TDM_IN_CH_4 ; 
 unsigned int RT5663_TDM_IN_CH_6 ; 
 unsigned int RT5663_TDM_IN_CH_8 ; 
 int RT5663_TDM_IN_CH_MASK ; 
 unsigned int RT5663_TDM_IN_LEN_20 ; 
 unsigned int RT5663_TDM_IN_LEN_24 ; 
 unsigned int RT5663_TDM_IN_LEN_32 ; 
 int RT5663_TDM_IN_LEN_MASK ; 
 int RT5663_TDM_MODE_MASK ; 
 unsigned int RT5663_TDM_MODE_TDM ; 
 unsigned int RT5663_TDM_OUT_CH_4 ; 
 unsigned int RT5663_TDM_OUT_CH_6 ; 
 unsigned int RT5663_TDM_OUT_CH_8 ; 
 int RT5663_TDM_OUT_CH_MASK ; 
 unsigned int RT5663_TDM_OUT_LEN_20 ; 
 unsigned int RT5663_TDM_OUT_LEN_24 ; 
 unsigned int RT5663_TDM_OUT_LEN_32 ; 
 int RT5663_TDM_OUT_LEN_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct rt5663_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int rt5663_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
	unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct rt5663_priv *rt5663 = snd_soc_component_get_drvdata(component);
	unsigned int val = 0, reg;

	if (rx_mask || tx_mask)
		val |= RT5663_TDM_MODE_TDM;

	switch (slots) {
	case 4:
		val |= RT5663_TDM_IN_CH_4;
		val |= RT5663_TDM_OUT_CH_4;
		break;
	case 6:
		val |= RT5663_TDM_IN_CH_6;
		val |= RT5663_TDM_OUT_CH_6;
		break;
	case 8:
		val |= RT5663_TDM_IN_CH_8;
		val |= RT5663_TDM_OUT_CH_8;
		break;
	case 2:
		break;
	default:
		return -EINVAL;
	}

	switch (slot_width) {
	case 20:
		val |= RT5663_TDM_IN_LEN_20;
		val |= RT5663_TDM_OUT_LEN_20;
		break;
	case 24:
		val |= RT5663_TDM_IN_LEN_24;
		val |= RT5663_TDM_OUT_LEN_24;
		break;
	case 32:
		val |= RT5663_TDM_IN_LEN_32;
		val |= RT5663_TDM_OUT_LEN_32;
		break;
	case 16:
		break;
	default:
		return -EINVAL;
	}

	switch (rt5663->codec_ver) {
	case CODEC_VER_1:
		reg = RT5663_TDM_2;
		break;
	case CODEC_VER_0:
		reg = RT5663_TDM_1;
		break;
	default:
		dev_err(component->dev, "Unknown CODEC Version\n");
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, reg, RT5663_TDM_MODE_MASK |
		RT5663_TDM_IN_CH_MASK | RT5663_TDM_OUT_CH_MASK |
		RT5663_TDM_IN_LEN_MASK | RT5663_TDM_OUT_LEN_MASK, val);

	return 0;
}