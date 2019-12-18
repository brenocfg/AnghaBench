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

/* Variables and functions */

__attribute__((used)) static u8 ieee80211_wmm_aci_aifsn(int aifsn, bool acm, int aci)
{
	u8 ret;

	ret = aifsn & 0x0f;
	if (acm)
		ret |= 0x10;
	ret |= (aci << 5) & 0x60;
	return ret;
}