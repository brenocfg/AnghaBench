#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct vif_params {scalar_t__ vht_mumimo_follow_addr; scalar_t__ vht_mumimo_groups; } ;
struct TYPE_6__ {scalar_t__* membership; scalar_t__* position; } ;
struct TYPE_7__ {TYPE_1__ mu_group; } ;
struct TYPE_10__ {int mu_mimo_owner; TYPE_2__ bss_conf; } ;
struct TYPE_8__ {int /*<<< orphan*/  mu_follow_addr; } ;
struct TYPE_9__ {TYPE_3__ mntr; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; TYPE_4__ u; } ;
typedef  int /*<<< orphan*/  membership ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_MU_GROUPS ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int WLAN_MEMBERSHIP_LEN ; 
 int WLAN_USER_POSITION_LEN ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int is_valid_ether_addr (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 

__attribute__((used)) static void ieee80211_set_mu_mimo_follow(struct ieee80211_sub_if_data *sdata,
					 struct vif_params *params)
{
	bool mu_mimo_groups = false;
	bool mu_mimo_follow = false;

	if (params->vht_mumimo_groups) {
		u64 membership;

		BUILD_BUG_ON(sizeof(membership) != WLAN_MEMBERSHIP_LEN);

		memcpy(sdata->vif.bss_conf.mu_group.membership,
		       params->vht_mumimo_groups, WLAN_MEMBERSHIP_LEN);
		memcpy(sdata->vif.bss_conf.mu_group.position,
		       params->vht_mumimo_groups + WLAN_MEMBERSHIP_LEN,
		       WLAN_USER_POSITION_LEN);
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_MU_GROUPS);
		/* don't care about endianness - just check for 0 */
		memcpy(&membership, params->vht_mumimo_groups,
		       WLAN_MEMBERSHIP_LEN);
		mu_mimo_groups = membership != 0;
	}

	if (params->vht_mumimo_follow_addr) {
		mu_mimo_follow =
			is_valid_ether_addr(params->vht_mumimo_follow_addr);
		ether_addr_copy(sdata->u.mntr.mu_follow_addr,
				params->vht_mumimo_follow_addr);
	}

	sdata->vif.mu_mimo_owner = mu_mimo_groups || mu_mimo_follow;
}