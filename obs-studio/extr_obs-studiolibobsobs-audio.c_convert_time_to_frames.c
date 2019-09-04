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
typedef  unsigned long long uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline size_t convert_time_to_frames(size_t sample_rate, uint64_t t)
{
	return (size_t)(t * (uint64_t)sample_rate / 1000000000ULL);
}