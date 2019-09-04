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
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 scalar_t__ __ieee80211_recalc_idle (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,scalar_t__) ; 

void ieee80211_recalc_idle(struct ieee80211_local *local)
{
	u32 change = __ieee80211_recalc_idle(local, false);
	if (change)
		ieee80211_hw_config(local, change);
}