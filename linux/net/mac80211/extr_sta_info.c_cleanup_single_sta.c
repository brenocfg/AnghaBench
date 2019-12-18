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
struct sta_info {struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cleanup_single_sta (struct sta_info*) ; 
 int /*<<< orphan*/  sta_info_free (struct ieee80211_local*,struct sta_info*) ; 

__attribute__((used)) static void cleanup_single_sta(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;

	__cleanup_single_sta(sta);
	sta_info_free(local, sta);
}