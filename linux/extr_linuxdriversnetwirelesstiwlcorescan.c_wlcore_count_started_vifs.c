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
struct wl1271 {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wlcore_started_vifs_iter ; 

__attribute__((used)) static int wlcore_count_started_vifs(struct wl1271 *wl)
{
	int count = 0;

	ieee80211_iterate_active_interfaces_atomic(wl->hw,
					IEEE80211_IFACE_ITER_RESUME_ALL,
					wlcore_started_vifs_iter, &count);
	return count;
}