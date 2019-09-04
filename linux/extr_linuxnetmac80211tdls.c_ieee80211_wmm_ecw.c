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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int ilog2 (scalar_t__) ; 

__attribute__((used)) static u8 ieee80211_wmm_ecw(u16 cw_min, u16 cw_max)
{
	return ((ilog2(cw_min + 1) << 0x0) & 0x0f) |
	       ((ilog2(cw_max + 1) << 0x4) & 0xf0);
}