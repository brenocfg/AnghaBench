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
 int EACCES ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  can_nice (struct task_struct*,int) ; 
 int security_task_setnice (struct task_struct*,int) ; 
 int /*<<< orphan*/  set_one_prio_perm (struct task_struct*) ; 
 int /*<<< orphan*/  set_user_nice (struct task_struct*,int) ; 
 int task_nice (struct task_struct*) ; 

__attribute__((used)) static int set_one_prio(struct task_struct *p, int niceval, int error)
{
	int no_nice;

	if (!set_one_prio_perm(p)) {
		error = -EPERM;
		goto out;
	}
	if (niceval < task_nice(p) && !can_nice(p, niceval)) {
		error = -EACCES;
		goto out;
	}
	no_nice = security_task_setnice(p, niceval);
	if (no_nice) {
		error = no_nice;
		goto out;
	}
	if (error == -ESRCH)
		error = 0;
	set_user_nice(p, niceval);
out:
	return error;
}