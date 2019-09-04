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

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int snd_soc_xlate_tdm_slot_mask(unsigned int slots,
					  unsigned int *tx_mask,
					  unsigned int *rx_mask)
{
	if (*tx_mask || *rx_mask)
		return 0;

	if (!slots)
		return -EINVAL;

	*tx_mask = (1 << slots) - 1;
	*rx_mask = (1 << slots) - 1;

	return 0;
}