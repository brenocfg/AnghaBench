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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  boost_mutex ; 
 struct task_struct** boost_tasks ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_torture_boost ; 
 int /*<<< orphan*/  rcu_torture_enable_rt_throttle () ; 
 int /*<<< orphan*/  torture_stop_kthread (int /*<<< orphan*/ ,struct task_struct*) ; 

__attribute__((used)) static int rcutorture_booster_cleanup(unsigned int cpu)
{
	struct task_struct *t;

	if (boost_tasks[cpu] == NULL)
		return 0;
	mutex_lock(&boost_mutex);
	t = boost_tasks[cpu];
	boost_tasks[cpu] = NULL;
	rcu_torture_enable_rt_throttle();
	mutex_unlock(&boost_mutex);

	/* This must be outside of the mutex, otherwise deadlock! */
	torture_stop_kthread(rcu_torture_boost, t);
	return 0;
}