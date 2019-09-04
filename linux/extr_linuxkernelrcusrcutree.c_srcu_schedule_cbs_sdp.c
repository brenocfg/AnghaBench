#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct srcu_data {int /*<<< orphan*/  work; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_gp_wq ; 
 int /*<<< orphan*/  srcu_queue_delayed_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void srcu_schedule_cbs_sdp(struct srcu_data *sdp, unsigned long delay)
{
	srcu_queue_delayed_work_on(sdp->cpu, rcu_gp_wq, &sdp->work, delay);
}