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
struct TYPE_2__ {int /*<<< orphan*/  ogm_wq; } ;
struct batadv_priv {TYPE_1__ bat_v; int /*<<< orphan*/  orig_interval; } ;

/* Variables and functions */
 int BATADV_JITTER ; 
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_event_workqueue ; 
 scalar_t__ delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_v_ogm_start_timer(struct batadv_priv *bat_priv)
{
	unsigned long msecs;
	/* this function may be invoked in different contexts (ogm rescheduling
	 * or hard_iface activation), but the work timer should not be reset
	 */
	if (delayed_work_pending(&bat_priv->bat_v.ogm_wq))
		return;

	msecs = atomic_read(&bat_priv->orig_interval) - BATADV_JITTER;
	msecs += prandom_u32() % (2 * BATADV_JITTER);
	queue_delayed_work(batadv_event_workqueue, &bat_priv->bat_v.ogm_wq,
			   msecs_to_jiffies(msecs));
}