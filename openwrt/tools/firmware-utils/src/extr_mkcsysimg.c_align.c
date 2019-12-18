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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t align(uint32_t base, uint32_t alignment)
{
	uint32_t ret;

	if (alignment) {
		ret = (base + alignment - 1);
		ret &= ~(alignment-1);
	} else {
		ret = base;
	}

	return ret;
}