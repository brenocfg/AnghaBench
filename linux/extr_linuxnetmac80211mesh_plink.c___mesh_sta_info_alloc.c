#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int wme; int aid; } ;
struct sta_info {TYPE_2__ sta; TYPE_1__* mesh; } ;
struct ieee80211_sub_if_data {TYPE_3__* local; } ;
struct TYPE_6__ {scalar_t__ num_sta; } ;
struct TYPE_4__ {int /*<<< orphan*/  plink_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_STA_ASSOC ; 
 int /*<<< orphan*/  IEEE80211_STA_AUTH ; 
 int /*<<< orphan*/  IEEE80211_STA_AUTHORIZED ; 
 scalar_t__ MESH_MAX_PLINKS ; 
 int /*<<< orphan*/  NL80211_PLINK_LISTEN ; 
 int mesh_allocate_aid (struct ieee80211_sub_if_data*) ; 
 struct sta_info* sta_info_alloc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_info_pre_move_state (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sta_info *
__mesh_sta_info_alloc(struct ieee80211_sub_if_data *sdata, u8 *hw_addr)
{
	struct sta_info *sta;
	int aid;

	if (sdata->local->num_sta >= MESH_MAX_PLINKS)
		return NULL;

	aid = mesh_allocate_aid(sdata);
	if (aid < 0)
		return NULL;

	sta = sta_info_alloc(sdata, hw_addr, GFP_KERNEL);
	if (!sta)
		return NULL;

	sta->mesh->plink_state = NL80211_PLINK_LISTEN;
	sta->sta.wme = true;
	sta->sta.aid = aid;

	sta_info_pre_move_state(sta, IEEE80211_STA_AUTH);
	sta_info_pre_move_state(sta, IEEE80211_STA_ASSOC);
	sta_info_pre_move_state(sta, IEEE80211_STA_AUTHORIZED);

	return sta;
}