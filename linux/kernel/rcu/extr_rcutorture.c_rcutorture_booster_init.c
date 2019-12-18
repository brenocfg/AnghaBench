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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  boost_mutex ; 
 int /*<<< orphan*/ ** boost_tasks ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 int /*<<< orphan*/  kthread_bind (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * kthread_create_on_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_rcu_torture_boost_ktrerror ; 
 int /*<<< orphan*/  rcu_torture_boost ; 
 int /*<<< orphan*/  rcu_torture_disable_rt_throttle () ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcutorture_booster_init(unsigned int cpu)
{
	int retval;

	if (boost_tasks[cpu] != NULL)
		return 0;  /* Already created, nothing more to do. */

	/* Don't allow time recalculation while creating a new task. */
	mutex_lock(&boost_mutex);
	rcu_torture_disable_rt_throttle();
	VERBOSE_TOROUT_STRING("Creating rcu_torture_boost task");
	boost_tasks[cpu] = kthread_create_on_node(rcu_torture_boost, NULL,
						  cpu_to_node(cpu),
						  "rcu_torture_boost");
	if (IS_ERR(boost_tasks[cpu])) {
		retval = PTR_ERR(boost_tasks[cpu]);
		VERBOSE_TOROUT_STRING("rcu_torture_boost task create failed");
		n_rcu_torture_boost_ktrerror++;
		boost_tasks[cpu] = NULL;
		mutex_unlock(&boost_mutex);
		return retval;
	}
	kthread_bind(boost_tasks[cpu], cpu);
	wake_up_process(boost_tasks[cpu]);
	mutex_unlock(&boost_mutex);
	return 0;
}