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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */

__attribute__((used)) static int intel_pt_tsc_cmp(uint64_t tsc1, uint64_t tsc2)
{
	const uint64_t halfway = (1ULL << 55);

	if (tsc1 == tsc2)
		return 0;

	if (tsc1 < tsc2) {
		if (tsc2 - tsc1 < halfway)
			return -1;
		else
			return 1;
	} else {
		if (tsc1 - tsc2 < halfway)
			return 1;
		else
			return -1;
	}
}