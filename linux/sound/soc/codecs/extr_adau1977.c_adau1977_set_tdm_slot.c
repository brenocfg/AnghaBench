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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct adau1977 {int slot_width; int max_master_fs; int /*<<< orphan*/  regmap; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 unsigned int ADAU1977_CHAN_MAP_FIRST_SLOT_OFFSET ; 
 unsigned int ADAU1977_CHAN_MAP_SECOND_SLOT_OFFSET ; 
 int /*<<< orphan*/  ADAU1977_REG_CMAP12 ; 
 int /*<<< orphan*/  ADAU1977_REG_CMAP34 ; 
 int /*<<< orphan*/  ADAU1977_REG_SAI_CTRL0 ; 
 int /*<<< orphan*/  ADAU1977_REG_SAI_CTRL1 ; 
 int /*<<< orphan*/  ADAU1977_REG_SAI_OVERTEMP ; 
 unsigned int ADAU1977_SAI_CTRL0_SAI_I2S ; 
 unsigned int ADAU1977_SAI_CTRL0_SAI_MASK ; 
 unsigned int ADAU1977_SAI_CTRL0_SAI_TDM_16 ; 
 unsigned int ADAU1977_SAI_CTRL0_SAI_TDM_2 ; 
 unsigned int ADAU1977_SAI_CTRL0_SAI_TDM_4 ; 
 unsigned int ADAU1977_SAI_CTRL0_SAI_TDM_8 ; 
 unsigned int ADAU1977_SAI_CTRL1_SLOT_WIDTH_16 ; 
 unsigned int ADAU1977_SAI_CTRL1_SLOT_WIDTH_24 ; 
 unsigned int ADAU1977_SAI_CTRL1_SLOT_WIDTH_32 ; 
 unsigned int ADAU1977_SAI_CTRL1_SLOT_WIDTH_MASK ; 
 unsigned int ADAU1977_SAI_OVERTEMP_DRV_C (int) ; 
 int EINVAL ; 
 unsigned int __ffs (unsigned int) ; 
 int min (int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adau1977* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1977_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
	unsigned int rx_mask, int slots, int width)
{
	struct adau1977 *adau1977 = snd_soc_component_get_drvdata(dai->component);
	unsigned int ctrl0, ctrl1, drv;
	unsigned int slot[4];
	unsigned int i;
	int ret;

	if (slots == 0) {
		/* 0 = No fixed slot width */
		adau1977->slot_width = 0;
		adau1977->max_master_fs = 192000;
		return regmap_update_bits(adau1977->regmap,
			ADAU1977_REG_SAI_CTRL0, ADAU1977_SAI_CTRL0_SAI_MASK,
			ADAU1977_SAI_CTRL0_SAI_I2S);
	}

	if (rx_mask == 0 || tx_mask != 0)
		return -EINVAL;

	drv = 0;
	for (i = 0; i < 4; i++) {
		slot[i] = __ffs(rx_mask);
		drv |= ADAU1977_SAI_OVERTEMP_DRV_C(i);
		rx_mask &= ~(1 << slot[i]);
		if (slot[i] >= slots)
			return -EINVAL;
		if (rx_mask == 0)
			break;
	}

	if (rx_mask != 0)
		return -EINVAL;

	switch (width) {
	case 16:
		ctrl1 = ADAU1977_SAI_CTRL1_SLOT_WIDTH_16;
		break;
	case 24:
		/* We can only generate 16 bit or 32 bit wide slots */
		if (adau1977->master)
			return -EINVAL;
		ctrl1 = ADAU1977_SAI_CTRL1_SLOT_WIDTH_24;
		break;
	case 32:
		ctrl1 = ADAU1977_SAI_CTRL1_SLOT_WIDTH_32;
		break;
	default:
		return -EINVAL;
	}

	switch (slots) {
	case 2:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_2;
		break;
	case 4:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_4;
		break;
	case 8:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_8;
		break;
	case 16:
		ctrl0 = ADAU1977_SAI_CTRL0_SAI_TDM_16;
		break;
	default:
		return -EINVAL;
	}

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_OVERTEMP,
		ADAU1977_SAI_OVERTEMP_DRV_C(0) |
		ADAU1977_SAI_OVERTEMP_DRV_C(1) |
		ADAU1977_SAI_OVERTEMP_DRV_C(2) |
		ADAU1977_SAI_OVERTEMP_DRV_C(3), drv);
	if (ret)
		return ret;

	ret = regmap_write(adau1977->regmap, ADAU1977_REG_CMAP12,
		(slot[1] << ADAU1977_CHAN_MAP_SECOND_SLOT_OFFSET) |
		(slot[0] << ADAU1977_CHAN_MAP_FIRST_SLOT_OFFSET));
	if (ret)
		return ret;

	ret = regmap_write(adau1977->regmap, ADAU1977_REG_CMAP34,
		(slot[3] << ADAU1977_CHAN_MAP_SECOND_SLOT_OFFSET) |
		(slot[2] << ADAU1977_CHAN_MAP_FIRST_SLOT_OFFSET));
	if (ret)
		return ret;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL0,
		ADAU1977_SAI_CTRL0_SAI_MASK, ctrl0);
	if (ret)
		return ret;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_SAI_CTRL1,
		ADAU1977_SAI_CTRL1_SLOT_WIDTH_MASK, ctrl1);
	if (ret)
		return ret;

	adau1977->slot_width = width;

	/* In master mode the maximum bitclock is 24.576 MHz */
	adau1977->max_master_fs = min(192000, 24576000 / width / slots);

	return 0;
}