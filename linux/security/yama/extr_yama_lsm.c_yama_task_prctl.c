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
struct task_struct {int /*<<< orphan*/  group_leader; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
#define  PR_SET_PTRACER 128 
 unsigned long PR_SET_PTRACER_ANY ; 
 struct task_struct* current ; 
 struct task_struct* find_get_task_by_vpid (unsigned long) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 struct task_struct* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  thread_group_leader (struct task_struct*) ; 
 int yama_ptracer_add (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  yama_ptracer_del (int /*<<< orphan*/ *,struct task_struct*) ; 

__attribute__((used)) static int yama_task_prctl(int option, unsigned long arg2, unsigned long arg3,
			   unsigned long arg4, unsigned long arg5)
{
	int rc = -ENOSYS;
	struct task_struct *myself = current;

	switch (option) {
	case PR_SET_PTRACER:
		/* Since a thread can call prctl(), find the group leader
		 * before calling _add() or _del() on it, since we want
		 * process-level granularity of control. The tracer group
		 * leader checking is handled later when walking the ancestry
		 * at the time of PTRACE_ATTACH check.
		 */
		rcu_read_lock();
		if (!thread_group_leader(myself))
			myself = rcu_dereference(myself->group_leader);
		get_task_struct(myself);
		rcu_read_unlock();

		if (arg2 == 0) {
			yama_ptracer_del(NULL, myself);
			rc = 0;
		} else if (arg2 == PR_SET_PTRACER_ANY || (int)arg2 == -1) {
			rc = yama_ptracer_add(NULL, myself);
		} else {
			struct task_struct *tracer;

			tracer = find_get_task_by_vpid(arg2);
			if (!tracer) {
				rc = -EINVAL;
			} else {
				rc = yama_ptracer_add(tracer, myself);
				put_task_struct(tracer);
			}
		}

		put_task_struct(myself);
		break;
	}

	return rc;
}