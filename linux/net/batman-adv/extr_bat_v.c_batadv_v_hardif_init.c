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
struct TYPE_2__ {int /*<<< orphan*/  aggr_wq; int /*<<< orphan*/  aggr_list_lock; int /*<<< orphan*/  aggr_list; scalar_t__ aggr_len; int /*<<< orphan*/  elp_interval; int /*<<< orphan*/  throughput_override; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  batadv_v_ogm_aggr_work ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void batadv_v_hardif_init(struct batadv_hard_iface *hard_iface)
{
	/* enable link throughput auto-detection by setting the throughput
	 * override to zero
	 */
	atomic_set(&hard_iface->bat_v.throughput_override, 0);
	atomic_set(&hard_iface->bat_v.elp_interval, 500);

	hard_iface->bat_v.aggr_len = 0;
	skb_queue_head_init(&hard_iface->bat_v.aggr_list);
	spin_lock_init(&hard_iface->bat_v.aggr_list_lock);
	INIT_DELAYED_WORK(&hard_iface->bat_v.aggr_wq,
			  batadv_v_ogm_aggr_work);
}