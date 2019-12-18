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
struct TYPE_2__ {int /*<<< orphan*/  elp_wq; int /*<<< orphan*/  elp_interval; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int BATADV_JITTER ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_event_workqueue ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_v_elp_start_timer(struct batadv_hard_iface *hard_iface)
{
	unsigned int msecs;

	msecs = atomic_read(&hard_iface->bat_v.elp_interval) - BATADV_JITTER;
	msecs += prandom_u32() % (2 * BATADV_JITTER);

	queue_delayed_work(batadv_event_workqueue, &hard_iface->bat_v.elp_wq,
			   msecs_to_jiffies(msecs));
}