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
typedef  void* u32 ;
struct stm32_sai_sub_data {int slot_width; int slots; int /*<<< orphan*/  regmap; void* slot_mask; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SAI_SLOT_SIZE_16 ; 
 int SAI_SLOT_SIZE_32 ; 
 int SAI_SLOT_SIZE_AUTO ; 
 int SAI_XSLOTR_NBSLOT_MASK ; 
 int SAI_XSLOTR_NBSLOT_SET (int) ; 
 int SAI_XSLOTR_SLOTEN_MASK ; 
 int SAI_XSLOTR_SLOTEN_SET (void*) ; 
 int SAI_XSLOTR_SLOTSZ_MASK ; 
 int SAI_XSLOTR_SLOTSZ_SET (int) ; 
 scalar_t__ STM_SAI_IS_CAPTURE (struct stm32_sai_sub_data*) ; 
 scalar_t__ STM_SAI_IS_PLAYBACK (struct stm32_sai_sub_data*) ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  STM_SAI_SLOTR_REGX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*,void*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_sai_set_dai_tdm_slot(struct snd_soc_dai *cpu_dai, u32 tx_mask,
				      u32 rx_mask, int slots, int slot_width)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int slotr, slotr_mask, slot_size;

	if (STM_SAI_PROTOCOL_IS_SPDIF(sai)) {
		dev_warn(cpu_dai->dev, "Slot setting relevant only for TDM\n");
		return 0;
	}

	dev_dbg(cpu_dai->dev, "Masks tx/rx:%#x/%#x, slots:%d, width:%d\n",
		tx_mask, rx_mask, slots, slot_width);

	switch (slot_width) {
	case 16:
		slot_size = SAI_SLOT_SIZE_16;
		break;
	case 32:
		slot_size = SAI_SLOT_SIZE_32;
		break;
	default:
		slot_size = SAI_SLOT_SIZE_AUTO;
		break;
	}

	slotr = SAI_XSLOTR_SLOTSZ_SET(slot_size) |
		SAI_XSLOTR_NBSLOT_SET(slots - 1);
	slotr_mask = SAI_XSLOTR_SLOTSZ_MASK | SAI_XSLOTR_NBSLOT_MASK;

	/* tx/rx mask set in machine init, if slot number defined in DT */
	if (STM_SAI_IS_PLAYBACK(sai)) {
		sai->slot_mask = tx_mask;
		slotr |= SAI_XSLOTR_SLOTEN_SET(tx_mask);
	}

	if (STM_SAI_IS_CAPTURE(sai)) {
		sai->slot_mask = rx_mask;
		slotr |= SAI_XSLOTR_SLOTEN_SET(rx_mask);
	}

	slotr_mask |= SAI_XSLOTR_SLOTEN_MASK;

	regmap_update_bits(sai->regmap, STM_SAI_SLOTR_REGX, slotr_mask, slotr);

	sai->slot_width = slot_width;
	sai->slots = slots;

	return 0;
}