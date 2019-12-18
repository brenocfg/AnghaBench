#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num_mcast_sta; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_mcast_sta; } ;
struct TYPE_8__ {TYPE_3__ vlan; TYPE_1__ ap; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__ vif; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

void ieee80211_vif_dec_num_mcast(struct ieee80211_sub_if_data *sdata)
{
	if (sdata->vif.type == NL80211_IFTYPE_AP)
		atomic_dec(&sdata->u.ap.num_mcast_sta);
	else if (sdata->vif.type == NL80211_IFTYPE_AP_VLAN)
		atomic_dec(&sdata->u.vlan.num_mcast_sta);
}