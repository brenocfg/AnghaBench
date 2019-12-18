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
struct rt5514_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int RT5514_CH_LEN_RX_20 ; 
 unsigned int RT5514_CH_LEN_RX_24 ; 
 unsigned int RT5514_CH_LEN_RX_32 ; 
 unsigned int RT5514_CH_LEN_RX_MASK ; 
 unsigned int RT5514_CH_LEN_TX_20 ; 
 unsigned int RT5514_CH_LEN_TX_24 ; 
 unsigned int RT5514_CH_LEN_TX_32 ; 
 unsigned int RT5514_CH_LEN_TX_MASK ; 
 int /*<<< orphan*/  RT5514_I2S_CTRL1 ; 
 int /*<<< orphan*/  RT5514_I2S_CTRL2 ; 
 unsigned int RT5514_TDMSLOT_SEL_RX_4CH ; 
 unsigned int RT5514_TDMSLOT_SEL_RX_6CH ; 
 unsigned int RT5514_TDMSLOT_SEL_RX_8CH ; 
 unsigned int RT5514_TDMSLOT_SEL_RX_MASK ; 
 unsigned int RT5514_TDMSLOT_SEL_TX_4CH ; 
 unsigned int RT5514_TDMSLOT_SEL_TX_6CH ; 
 unsigned int RT5514_TDMSLOT_SEL_TX_8CH ; 
 unsigned int RT5514_TDMSLOT_SEL_TX_MASK ; 
 unsigned int RT5514_TDM_DOCKING_MODE ; 
 unsigned int RT5514_TDM_DOCKING_START_MASK ; 
 unsigned int RT5514_TDM_DOCKING_START_SLOT0 ; 
 unsigned int RT5514_TDM_DOCKING_START_SLOT4 ; 
 unsigned int RT5514_TDM_DOCKING_VALID_CH2 ; 
 unsigned int RT5514_TDM_DOCKING_VALID_CH4 ; 
 unsigned int RT5514_TDM_DOCKING_VALID_CH_MASK ; 
 unsigned int RT5514_TDM_MODE ; 
 unsigned int RT5514_TDM_MODE2 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct rt5514_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int rt5514_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct rt5514_priv *rt5514 = snd_soc_component_get_drvdata(component);
	unsigned int val = 0, val2 = 0;

	if (rx_mask || tx_mask)
		val |= RT5514_TDM_MODE;

	switch (tx_mask) {
	case 0x3:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH2 |
			RT5514_TDM_DOCKING_START_SLOT0;
		break;

	case 0x30:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH2 |
			RT5514_TDM_DOCKING_START_SLOT4;
		break;

	case 0xf:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH4 |
			RT5514_TDM_DOCKING_START_SLOT0;
		break;

	case 0xf0:
		val2 |= RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH4 |
			RT5514_TDM_DOCKING_START_SLOT4;
		break;

	default:
		break;
	}



	switch (slots) {
	case 4:
		val |= RT5514_TDMSLOT_SEL_RX_4CH | RT5514_TDMSLOT_SEL_TX_4CH;
		break;

	case 6:
		val |= RT5514_TDMSLOT_SEL_RX_6CH | RT5514_TDMSLOT_SEL_TX_6CH;
		break;

	case 8:
		val |= RT5514_TDMSLOT_SEL_RX_8CH | RT5514_TDMSLOT_SEL_TX_8CH;
		break;

	case 2:
	default:
		break;
	}

	switch (slot_width) {
	case 20:
		val |= RT5514_CH_LEN_RX_20 | RT5514_CH_LEN_TX_20;
		break;

	case 24:
		val |= RT5514_CH_LEN_RX_24 | RT5514_CH_LEN_TX_24;
		break;

	case 25:
		val |= RT5514_TDM_MODE2;
		break;

	case 32:
		val |= RT5514_CH_LEN_RX_32 | RT5514_CH_LEN_TX_32;
		break;

	case 16:
	default:
		break;
	}

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL1, RT5514_TDM_MODE |
		RT5514_TDMSLOT_SEL_RX_MASK | RT5514_TDMSLOT_SEL_TX_MASK |
		RT5514_CH_LEN_RX_MASK | RT5514_CH_LEN_TX_MASK |
		RT5514_TDM_MODE2, val);

	regmap_update_bits(rt5514->regmap, RT5514_I2S_CTRL2,
		RT5514_TDM_DOCKING_MODE | RT5514_TDM_DOCKING_VALID_CH_MASK |
		RT5514_TDM_DOCKING_START_MASK, val2);

	return 0;
}