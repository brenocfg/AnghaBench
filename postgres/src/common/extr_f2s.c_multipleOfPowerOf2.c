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
typedef  unsigned int uint32 ;

/* Variables and functions */

__attribute__((used)) static inline bool
multipleOfPowerOf2(const uint32 value, const uint32 p)
{
	/* return __builtin_ctz(value) >= p; */
	return (value & ((1u << p) - 1)) == 0;
}