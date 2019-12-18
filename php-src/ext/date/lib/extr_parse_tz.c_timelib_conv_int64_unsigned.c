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

__attribute__((used)) static inline uint64_t timelib_conv_int64_unsigned(uint64_t value)
{
	return
		((value & 0x00000000000000ff) << 56) +
		((value & 0x000000000000ff00) << 40) +
		((value & 0x0000000000ff0000) << 24) +
		((value & 0x00000000ff000000) <<  8) +
		((value & 0x000000ff00000000) >>  8) +
		((value & 0x0000ff0000000000) >> 24) +
		((value & 0x00ff000000000000) >> 40) +
		((value & 0xff00000000000000) >> 56);
}