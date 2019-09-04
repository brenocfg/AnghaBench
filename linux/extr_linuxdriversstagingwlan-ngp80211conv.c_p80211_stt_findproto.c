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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ ETH_P_AARP ; 

int p80211_stt_findproto(u16 proto)
{
	/* Always return found for now.  This is the behavior used by the */
	/* Zoom Win95 driver when 802.1h mode is selected */
	/* TODO: If necessary, add an actual search we'll probably
	 * need this to match the CMAC's way of doing things.
	 * Need to do some testing to confirm.
	 */

	if (proto == ETH_P_AARP)	/* APPLETALK */
		return 1;

	return 0;
}