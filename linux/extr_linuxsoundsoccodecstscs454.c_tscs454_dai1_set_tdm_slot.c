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

/* Variables and functions */
 int EINVAL ; 
 unsigned int FV_TDMDSS_16 ; 
 unsigned int FV_TDMDSS_24 ; 
 unsigned int FV_TDMDSS_32 ; 
 unsigned int FV_TDMSI_2 ; 
 unsigned int FV_TDMSI_4 ; 
 unsigned int FV_TDMSI_6 ; 
 unsigned int FV_TDMSO_2 ; 
 unsigned int FV_TDMSO_4 ; 
 unsigned int FV_TDMSO_6 ; 
 int /*<<< orphan*/  R_TDMCTL1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int tscs454_dai1_set_tdm_slot(struct snd_soc_dai *dai,
		unsigned int tx_mask, unsigned int rx_mask, int slots,
		int slot_width)
{
	struct snd_soc_component *component = dai->component;
	unsigned int val;
	int ret;

	if (!slots)
		return 0;

	if (tx_mask >= (1 << slots) || rx_mask >= (1 << slots)) {
		ret = -EINVAL;
		dev_err(component->dev, "Invalid TDM slot mask (%d)\n", ret);
		return ret;
	}

	switch (slots) {
	case 2:
		val = FV_TDMSO_2 | FV_TDMSI_2;
		break;
	case 4:
		val = FV_TDMSO_4 | FV_TDMSI_4;
		break;
	case 6:
		val = FV_TDMSO_6 | FV_TDMSI_6;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Invalid number of slots (%d)\n", ret);
		return ret;
	}

	switch (slot_width) {
	case 16:
		val = val | FV_TDMDSS_16;
		break;
	case 24:
		val = val | FV_TDMDSS_24;
		break;
	case 32:
		val = val | FV_TDMDSS_32;
		break;
	default:
		ret = -EINVAL;
		dev_err(component->dev, "Invalid TDM slot width (%d)\n", ret);
		return ret;
	}
	ret = snd_soc_component_write(component, R_TDMCTL1, val);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set slots (%d)\n", ret);
		return ret;
	}

	return 0;
}