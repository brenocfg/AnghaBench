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
 int /*<<< orphan*/  RT5659_TDM_CTRL_1 ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int rt5659_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	unsigned int val = 0;

	if (rx_mask || tx_mask)
		val |= (1 << 15);

	switch (slots) {
	case 4:
		val |= (1 << 10);
		val |= (1 << 8);
		break;
	case 6:
		val |= (2 << 10);
		val |= (2 << 8);
		break;
	case 8:
		val |= (3 << 10);
		val |= (3 << 8);
		break;
	case 2:
		break;
	default:
		return -EINVAL;
	}

	switch (slot_width) {
	case 20:
		val |= (1 << 6);
		val |= (1 << 4);
		break;
	case 24:
		val |= (2 << 6);
		val |= (2 << 4);
		break;
	case 32:
		val |= (3 << 6);
		val |= (3 << 4);
		break;
	case 16:
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, RT5659_TDM_CTRL_1, 0x8ff0, val);

	return 0;
}