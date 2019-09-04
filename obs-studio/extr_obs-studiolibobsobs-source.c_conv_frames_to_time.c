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

__attribute__((used)) static inline uint64_t conv_frames_to_time(const size_t sample_rate,
		const size_t frames)
{
	if (!sample_rate)
		return 0;
	
	return (uint64_t)frames * 1000000000ULL / (uint64_t)sample_rate;
}