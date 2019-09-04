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
struct il3945_rs_sta {int /*<<< orphan*/  rate_scale_flush; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_rs_free_sta(void *il_priv, struct ieee80211_sta *sta, void *il_sta)
{
	struct il3945_rs_sta *rs_sta = il_sta;

	/*
	 * Be careful not to use any members of il3945_rs_sta (like trying
	 * to use il_priv to print out debugging) since it may not be fully
	 * initialized at this point.
	 */
	del_timer_sync(&rs_sta->rate_scale_flush);
}