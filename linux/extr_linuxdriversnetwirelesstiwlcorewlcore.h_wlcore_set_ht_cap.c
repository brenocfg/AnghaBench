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
struct wl1271 {int /*<<< orphan*/ * ht_cap; } ;
struct ieee80211_sta_ht_cap {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_sta_ht_cap*,int) ; 

__attribute__((used)) static inline void
wlcore_set_ht_cap(struct wl1271 *wl, enum nl80211_band band,
		  struct ieee80211_sta_ht_cap *ht_cap)
{
	memcpy(&wl->ht_cap[band], ht_cap, sizeof(*ht_cap));
}