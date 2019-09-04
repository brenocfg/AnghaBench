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
typedef  unsigned long long const uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline size_t conv_time_to_frames(const size_t sample_rate,
		const uint64_t duration)
{
	return (size_t)(duration * (uint64_t)sample_rate / 1000000000ULL);
}