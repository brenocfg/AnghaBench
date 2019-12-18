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
struct timer_list {int dummy; } ;
struct ieee80211_if_managed {int connection_loss; int /*<<< orphan*/  beacon_connection_loss_work; int /*<<< orphan*/  csa_waiting_bcn; } ;
struct TYPE_8__ {struct ieee80211_if_managed mgd; } ;
struct TYPE_9__ {scalar_t__ csa_active; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__* local; TYPE_4__ vif; } ;
struct TYPE_7__ {int /*<<< orphan*/  bcn_mon_timer; } ;
struct TYPE_10__ {TYPE_2__ mgd; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* sdata ; 
 TYPE_5__ u ; 

__attribute__((used)) static void ieee80211_sta_bcn_mon_timer(struct timer_list *t)
{
	struct ieee80211_sub_if_data *sdata =
		from_timer(sdata, t, u.mgd.bcn_mon_timer);
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	if (sdata->vif.csa_active && !ifmgd->csa_waiting_bcn)
		return;

	sdata->u.mgd.connection_loss = false;
	ieee80211_queue_work(&sdata->local->hw,
			     &sdata->u.mgd.beacon_connection_loss_work);
}