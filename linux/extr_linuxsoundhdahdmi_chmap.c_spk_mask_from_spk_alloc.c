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
 int ARRAY_SIZE (int*) ; 
 int* eld_speaker_allocation_bits ; 

__attribute__((used)) static int spk_mask_from_spk_alloc(int spk_alloc)
{
	int i;
	int spk_mask = eld_speaker_allocation_bits[0];

	for (i = 0; i < ARRAY_SIZE(eld_speaker_allocation_bits); i++) {
		if (spk_alloc & (1 << i))
			spk_mask |= eld_speaker_allocation_bits[i];
	}

	return spk_mask;
}