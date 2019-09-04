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
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int mc13783_set_tdm_slot_codec(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask, int slots,
	int slot_width)
{
	struct snd_soc_component *component = dai->component;
	unsigned int val = 0;
	unsigned int mask = 0x3f;

	if (slots != 4)
		return -EINVAL;

	if (tx_mask != 0x3)
		return -EINVAL;

	val |= (0x00 << 2);	/* primary timeslot RX/TX(?) is 0 */
	val |= (0x01 << 4);	/* secondary timeslot TX is 1 */

	snd_soc_component_update_bits(component, MC13783_SSI_NETWORK, mask, val);

	return 0;
}