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
struct ssm2518 {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int EINVAL ; 
 int SSM2518_CHAN_MAP_LEFT_SLOT_OFFSET ; 
 int SSM2518_CHAN_MAP_RIGHT_SLOT_OFFSET ; 
 int /*<<< orphan*/  SSM2518_REG_CHAN_MAP ; 
 int /*<<< orphan*/  SSM2518_REG_SAI_CTRL1 ; 
 int /*<<< orphan*/  SSM2518_REG_SAI_CTRL2 ; 
 unsigned int SSM2518_SAI_CTRL1_SAI_I2S ; 
 int /*<<< orphan*/  SSM2518_SAI_CTRL1_SAI_MASK ; 
 unsigned int SSM2518_SAI_CTRL1_SAI_MONO ; 
 unsigned int SSM2518_SAI_CTRL1_SAI_TDM_16 ; 
 unsigned int SSM2518_SAI_CTRL1_SAI_TDM_2 ; 
 unsigned int SSM2518_SAI_CTRL1_SAI_TDM_4 ; 
 unsigned int SSM2518_SAI_CTRL1_SAI_TDM_8 ; 
 unsigned int SSM2518_SAI_CTRL2_SLOT_WIDTH_16 ; 
 unsigned int SSM2518_SAI_CTRL2_SLOT_WIDTH_24 ; 
 unsigned int SSM2518_SAI_CTRL2_SLOT_WIDTH_32 ; 
 int /*<<< orphan*/  SSM2518_SAI_CTRL2_SLOT_WIDTH_MASK ; 
 int __ffs (unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ssm2518* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssm2518_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
	unsigned int rx_mask, int slots, int width)
{
	struct ssm2518 *ssm2518 = snd_soc_component_get_drvdata(dai->component);
	unsigned int ctrl1, ctrl2;
	int left_slot, right_slot;
	int ret;

	if (slots == 0)
		return regmap_update_bits(ssm2518->regmap,
			SSM2518_REG_SAI_CTRL1, SSM2518_SAI_CTRL1_SAI_MASK,
			SSM2518_SAI_CTRL1_SAI_I2S);

	if (tx_mask == 0 || rx_mask != 0)
		return -EINVAL;

	if (slots == 1) {
		if (tx_mask != 1)
			return -EINVAL;
		left_slot = 0;
		right_slot = 0;
	} else {
		/* We assume the left channel < right channel */
		left_slot = __ffs(tx_mask);
		tx_mask &= ~(1 << left_slot);
		if (tx_mask == 0) {
			right_slot = left_slot;
		} else {
			right_slot = __ffs(tx_mask);
			tx_mask &= ~(1 << right_slot);
		}
	}

	if (tx_mask != 0 || left_slot >= slots || right_slot >= slots)
		return -EINVAL;

	switch (width) {
	case 16:
		ctrl2 = SSM2518_SAI_CTRL2_SLOT_WIDTH_16;
		break;
	case 24:
		ctrl2 = SSM2518_SAI_CTRL2_SLOT_WIDTH_24;
		break;
	case 32:
		ctrl2 = SSM2518_SAI_CTRL2_SLOT_WIDTH_32;
		break;
	default:
		return -EINVAL;
	}

	switch (slots) {
	case 1:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_MONO;
		break;
	case 2:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_2;
		break;
	case 4:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_4;
		break;
	case 8:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_8;
		break;
	case 16:
		ctrl1 = SSM2518_SAI_CTRL1_SAI_TDM_16;
		break;
	default:
		return -EINVAL;
	}

	ret = regmap_write(ssm2518->regmap, SSM2518_REG_CHAN_MAP,
		(left_slot << SSM2518_CHAN_MAP_LEFT_SLOT_OFFSET) |
		(right_slot << SSM2518_CHAN_MAP_RIGHT_SLOT_OFFSET));
	if (ret)
		return ret;

	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_SAI_CTRL1,
		SSM2518_SAI_CTRL1_SAI_MASK, ctrl1);
	if (ret)
		return ret;

	return regmap_update_bits(ssm2518->regmap, SSM2518_REG_SAI_CTRL2,
		SSM2518_SAI_CTRL2_SLOT_WIDTH_MASK, ctrl2);
}