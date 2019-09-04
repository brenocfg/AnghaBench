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
typedef  size_t uint_fast32_t ;
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t NSEC_PER_SEC ; 

__attribute__((used)) static inline uint64_t samples_to_ns(size_t frames, uint_fast32_t rate)
{
	return frames * NSEC_PER_SEC / rate;
}