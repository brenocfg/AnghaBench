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
struct TYPE_2__ {scalar_t__ time_scan_cached; } ;

/* Variables and functions */
 int HZ ; 
 unsigned long jiffies ; 
 TYPE_1__* last_scanned_shadow ; 
 int nl80211_SCAN_RESULT_EXPIRE ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline bool wilc_wfi_cfg_scan_time_expired(int i)
{
	unsigned long now = jiffies;

	if (time_after(now, last_scanned_shadow[i].time_scan_cached +
		       (unsigned long)(nl80211_SCAN_RESULT_EXPIRE - (1 * HZ))))
		return true;
	else
		return false;
}