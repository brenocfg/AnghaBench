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
typedef  unsigned long long u64 ;

/* Variables and functions */
 unsigned long long PERF_SAMPLE_MASK ; 

int __perf_evsel__sample_size(u64 sample_type)
{
	u64 mask = sample_type & PERF_SAMPLE_MASK;
	int size = 0;
	int i;

	for (i = 0; i < 64; i++) {
		if (mask & (1ULL << i))
			size++;
	}

	size *= sizeof(u64);

	return size;
}