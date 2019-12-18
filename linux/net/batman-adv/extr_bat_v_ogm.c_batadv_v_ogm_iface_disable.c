#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  aggr_list_lock; int /*<<< orphan*/  aggr_wq; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_v_ogm_aggr_list_free (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_v_ogm_iface_disable(struct batadv_hard_iface *hard_iface)
{
	cancel_delayed_work_sync(&hard_iface->bat_v.aggr_wq);

	spin_lock_bh(&hard_iface->bat_v.aggr_list_lock);
	batadv_v_ogm_aggr_list_free(hard_iface);
	spin_unlock_bh(&hard_iface->bat_v.aggr_list_lock);
}