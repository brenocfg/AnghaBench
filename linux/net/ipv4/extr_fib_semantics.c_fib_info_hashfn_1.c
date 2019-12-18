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
typedef  int u8 ;
typedef  unsigned int u32 ;

/* Variables and functions */

__attribute__((used)) static unsigned int fib_info_hashfn_1(int init_val, u8 protocol, u8 scope,
				      u32 prefsrc, u32 priority)
{
	unsigned int val = init_val;

	val ^= (protocol << 8) | scope;
	val ^= prefsrc;
	val ^= priority;

	return val;
}