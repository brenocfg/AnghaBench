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
typedef  int /*<<< orphan*/  uint_fast32_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ os_gettime_ns () ; 
 scalar_t__ samples_to_ns (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t get_sample_time(size_t frames, uint_fast32_t rate)
{
	return os_gettime_ns() - samples_to_ns(frames, rate);
}