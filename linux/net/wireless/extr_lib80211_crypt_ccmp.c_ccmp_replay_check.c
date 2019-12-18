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
typedef  int u32 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */

__attribute__((used)) static inline int ccmp_replay_check(u8 *pn_n, u8 *pn_o)
{
	u32 iv32_n, iv16_n;
	u32 iv32_o, iv16_o;

	iv32_n = (pn_n[0] << 24) | (pn_n[1] << 16) | (pn_n[2] << 8) | pn_n[3];
	iv16_n = (pn_n[4] << 8) | pn_n[5];

	iv32_o = (pn_o[0] << 24) | (pn_o[1] << 16) | (pn_o[2] << 8) | pn_o[3];
	iv16_o = (pn_o[4] << 8) | pn_o[5];

	if ((s32)iv32_n - (s32)iv32_o < 0 ||
	    (iv32_n == iv32_o && iv16_n <= iv16_o))
		return 1;
	return 0;
}