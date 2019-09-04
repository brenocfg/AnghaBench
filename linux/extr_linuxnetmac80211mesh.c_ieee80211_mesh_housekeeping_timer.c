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
struct timer_list {int dummy; } ;
struct ieee80211_if_mesh {int /*<<< orphan*/  wrkq_flags; } ;
struct TYPE_5__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  work; TYPE_2__ u; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  housekeeping_timer; } ;
struct TYPE_6__ {TYPE_1__ mesh; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESH_WORK_HOUSEKEEPING ; 
 struct ieee80211_sub_if_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* sdata ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ u ; 

__attribute__((used)) static void ieee80211_mesh_housekeeping_timer(struct timer_list *t)
{
	struct ieee80211_sub_if_data *sdata =
		from_timer(sdata, t, u.mesh.housekeeping_timer);
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

	set_bit(MESH_WORK_HOUSEKEEPING, &ifmsh->wrkq_flags);

	ieee80211_queue_work(&local->hw, &sdata->work);
}