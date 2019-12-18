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
struct rt5645_priv {int codec_type; } ;

/* Variables and functions */
 int CODEC_TYPE_RT5645 ; 
#define  CODEC_TYPE_RT5650 128 
 int /*<<< orphan*/  RT5645_BASS_BACK ; 
 unsigned int RT5645_G_BB_BST_25DB ; 
 unsigned int RT5645_G_BB_BST_MASK ; 
 int /*<<< orphan*/  RT5645_TDM_CTRL_1 ; 
 struct rt5645_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int rt5645_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct rt5645_priv *rt5645 = snd_soc_component_get_drvdata(component);
	unsigned int i_slot_sft, o_slot_sft, i_width_sht, o_width_sht, en_sft;
	unsigned int mask, val = 0;

	switch (rt5645->codec_type) {
	case CODEC_TYPE_RT5650:
		en_sft = 15;
		i_slot_sft = 10;
		o_slot_sft = 8;
		i_width_sht = 6;
		o_width_sht = 4;
		mask = 0x8ff0;
		break;
	default:
		en_sft = 14;
		i_slot_sft = o_slot_sft = 12;
		i_width_sht = o_width_sht = 10;
		mask = 0x7c00;
		break;
	}
	if (rx_mask || tx_mask) {
		val |= (1 << en_sft);
		if (rt5645->codec_type == CODEC_TYPE_RT5645)
			snd_soc_component_update_bits(component, RT5645_BASS_BACK,
				RT5645_G_BB_BST_MASK, RT5645_G_BB_BST_25DB);
	}

	switch (slots) {
	case 4:
		val |= (1 << i_slot_sft) | (1 << o_slot_sft);
		break;
	case 6:
		val |= (2 << i_slot_sft) | (2 << o_slot_sft);
		break;
	case 8:
		val |= (3 << i_slot_sft) | (3 << o_slot_sft);
		break;
	case 2:
	default:
		break;
	}

	switch (slot_width) {
	case 20:
		val |= (1 << i_width_sht) | (1 << o_width_sht);
		break;
	case 24:
		val |= (2 << i_width_sht) | (2 << o_width_sht);
		break;
	case 32:
		val |= (3 << i_width_sht) | (3 << o_width_sht);
		break;
	case 16:
	default:
		break;
	}

	snd_soc_component_update_bits(component, RT5645_TDM_CTRL_1, mask, val);

	return 0;
}