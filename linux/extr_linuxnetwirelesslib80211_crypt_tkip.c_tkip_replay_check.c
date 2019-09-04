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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */

__attribute__((used)) static inline int tkip_replay_check(u32 iv32_n, u16 iv16_n,
				    u32 iv32_o, u16 iv16_o)
{
	if ((s32)iv32_n - (s32)iv32_o < 0 ||
	    (iv32_n == iv32_o && iv16_n <= iv16_o))
		return 1;
	return 0;
}