#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* rx_mask; } ;
struct ieee80211_ht_cap {TYPE_1__ mcs; } ;

/* Variables and functions */

unsigned int update_MSC_rate(struct ieee80211_ht_cap *pHT_caps)
{
	unsigned int mask = 0;

	mask = (pHT_caps->mcs.rx_mask[0] << 12) |
	       (pHT_caps->mcs.rx_mask[1] << 20);

	return mask;
}