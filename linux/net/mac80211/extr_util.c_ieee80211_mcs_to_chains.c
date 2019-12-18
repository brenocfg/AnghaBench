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
struct ieee80211_mcs_info {scalar_t__* rx_mask; } ;

/* Variables and functions */

u8 ieee80211_mcs_to_chains(const struct ieee80211_mcs_info *mcs)
{
	if (!mcs)
		return 1;

	/* TODO: consider rx_highest */

	if (mcs->rx_mask[3])
		return 4;
	if (mcs->rx_mask[2])
		return 3;
	if (mcs->rx_mask[1])
		return 2;
	return 1;
}