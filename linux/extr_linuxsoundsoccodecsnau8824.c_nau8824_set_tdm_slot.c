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
struct nau8824 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NAU8824_REG_PORT0_LEFT_TIME_SLOT ; 
 int /*<<< orphan*/  NAU8824_REG_TDM_CTRL ; 
 unsigned int NAU8824_TDM_DACL_RX_MASK ; 
 unsigned int NAU8824_TDM_DACR_RX_MASK ; 
 unsigned int NAU8824_TDM_DACR_RX_SFT ; 
 unsigned int NAU8824_TDM_MODE ; 
 unsigned int NAU8824_TDM_OFFSET_EN ; 
 unsigned int NAU8824_TDM_TX_MASK ; 
 unsigned int NAU8824_TSLOT_L_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct nau8824* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int nau8824_set_tdm_slot(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	unsigned int tslot_l = 0, ctrl_val = 0;

	if (slots > 4 || ((tx_mask & 0xf0) && (tx_mask & 0xf)) ||
		((rx_mask & 0xf0) && (rx_mask & 0xf)) ||
		((rx_mask & 0xf0) && (tx_mask & 0xf)) ||
		((rx_mask & 0xf) && (tx_mask & 0xf0)))
		return -EINVAL;

	ctrl_val |= (NAU8824_TDM_MODE | NAU8824_TDM_OFFSET_EN);
	if (tx_mask & 0xf0) {
		tslot_l = 4 * slot_width;
		ctrl_val |= (tx_mask >> 4);
	} else {
		ctrl_val |= tx_mask;
	}
	if (rx_mask & 0xf0)
		ctrl_val |= ((rx_mask >> 4) << NAU8824_TDM_DACR_RX_SFT);
	else
		ctrl_val |= (rx_mask << NAU8824_TDM_DACR_RX_SFT);

	regmap_update_bits(nau8824->regmap, NAU8824_REG_TDM_CTRL,
		NAU8824_TDM_MODE | NAU8824_TDM_OFFSET_EN |
		NAU8824_TDM_DACL_RX_MASK | NAU8824_TDM_DACR_RX_MASK |
		NAU8824_TDM_TX_MASK, ctrl_val);
	regmap_update_bits(nau8824->regmap, NAU8824_REG_PORT0_LEFT_TIME_SLOT,
		NAU8824_TSLOT_L_MASK, tslot_l);

	return 0;
}