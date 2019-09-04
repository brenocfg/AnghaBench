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
struct workqueue_struct {int dummy; } ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int queue_delayed_work (struct workqueue_struct*,struct delayed_work*,unsigned long) ; 
 int queue_delayed_work_on (int,struct workqueue_struct*,struct delayed_work*,unsigned long) ; 
 int /*<<< orphan*/  srcu_online ; 

__attribute__((used)) static bool srcu_queue_delayed_work_on(int cpu, struct workqueue_struct *wq,
				       struct delayed_work *dwork,
				       unsigned long delay)
{
	bool ret;

	preempt_disable();
	if (READ_ONCE(per_cpu(srcu_online, cpu)))
		ret = queue_delayed_work_on(cpu, wq, dwork, delay);
	else
		ret = queue_delayed_work(wq, dwork, delay);
	preempt_enable();
	return ret;
}