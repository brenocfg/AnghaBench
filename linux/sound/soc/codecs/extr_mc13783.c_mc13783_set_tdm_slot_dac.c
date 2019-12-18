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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MC13783_SSI_NETWORK ; 
 unsigned int SSI_NETWORK_DAC_RXSLOT_0_1 ; 
 unsigned int SSI_NETWORK_DAC_RXSLOT_2_3 ; 
 unsigned int SSI_NETWORK_DAC_RXSLOT_4_5 ; 
 unsigned int SSI_NETWORK_DAC_RXSLOT_6_7 ; 
 unsigned int SSI_NETWORK_DAC_RXSLOT_MASK ; 
 unsigned int SSI_NETWORK_DAC_SLOTS_2 ; 
 unsigned int SSI_NETWORK_DAC_SLOTS_4 ; 
 unsigned int SSI_NETWORK_DAC_SLOTS_8 ; 
 unsigned int SSI_NETWORK_DAC_SLOT_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int mc13783_set_tdm_slot_dac(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots,
	int slot_width)
{
	struct snd_soc_component *component = dai->component;
	unsigned int val = 0;
	unsigned int mask = SSI_NETWORK_DAC_SLOT_MASK |
				SSI_NETWORK_DAC_RXSLOT_MASK;

	switch (slots) {
	case 2:
		val |= SSI_NETWORK_DAC_SLOTS_2;
		break;
	case 4:
		val |= SSI_NETWORK_DAC_SLOTS_4;
		break;
	case 8:
		val |= SSI_NETWORK_DAC_SLOTS_8;
		break;
	default:
		return -EINVAL;
	}

	switch (rx_mask) {
	case 0x03:
		val |= SSI_NETWORK_DAC_RXSLOT_0_1;
		break;
	case 0x0c:
		val |= SSI_NETWORK_DAC_RXSLOT_2_3;
		break;
	case 0x30:
		val |= SSI_NETWORK_DAC_RXSLOT_4_5;
		break;
	case 0xc0:
		val |= SSI_NETWORK_DAC_RXSLOT_6_7;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, MC13783_SSI_NETWORK, mask, val);

	return 0;
}