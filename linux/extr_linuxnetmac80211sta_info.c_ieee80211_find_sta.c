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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_sta {int dummy; } ;
struct sta_info {struct ieee80211_sta sta; int /*<<< orphan*/  uploaded; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 struct sta_info* sta_info_get_bss (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vif_to_sdata (struct ieee80211_vif*) ; 

struct ieee80211_sta *ieee80211_find_sta(struct ieee80211_vif *vif,
					 const u8 *addr)
{
	struct sta_info *sta;

	if (!vif)
		return NULL;

	sta = sta_info_get_bss(vif_to_sdata(vif), addr);
	if (!sta)
		return NULL;

	if (!sta->uploaded)
		return NULL;

	return &sta->sta;
}