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
struct TYPE_2__ {int /*<<< orphan*/  aggr_wq; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int BATADV_MAX_AGGREGATION_MS ; 
 int /*<<< orphan*/  batadv_event_workqueue ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 unsigned int prandom_u32 () ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_v_ogm_start_queue_timer(struct batadv_hard_iface *hard_iface)
{
	unsigned int msecs = BATADV_MAX_AGGREGATION_MS * 1000;

	/* msecs * [0.9, 1.1] */
	msecs += prandom_u32() % (msecs / 5) - (msecs / 10);
	queue_delayed_work(batadv_event_workqueue, &hard_iface->bat_v.aggr_wq,
			   msecs_to_jiffies(msecs / 1000));
}