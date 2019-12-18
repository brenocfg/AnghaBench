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

__attribute__((used)) static uint64_t intel_pt_8b_tsc(uint64_t timestamp, uint64_t ref_timestamp)
{
	timestamp |= (ref_timestamp & (0xffULL << 56));

	if (timestamp < ref_timestamp) {
		if (ref_timestamp - timestamp > (1ULL << 55))
			timestamp += (1ULL << 56);
	} else {
		if (timestamp - ref_timestamp > (1ULL << 55))
			timestamp -= (1ULL << 56);
	}

	return timestamp;
}