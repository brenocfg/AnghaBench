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
typedef  int uint64_t ;

/* Variables and functions */
 int KPF_ALL_BITS ; 
 int nr_bit_filters ; 
 int* opt_bits ; 
 int* opt_mask ; 

__attribute__((used)) static int bit_mask_ok(uint64_t flags)
{
	int i;

	for (i = 0; i < nr_bit_filters; i++) {
		if (opt_bits[i] == KPF_ALL_BITS) {
			if ((flags & opt_mask[i]) == 0)
				return 0;
		} else {
			if ((flags & opt_mask[i]) != opt_bits[i])
				return 0;
		}
	}

	return 1;
}