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
struct user_namespace {int dummy; } ;
struct pid_namespace {int dummy; } ;

/* Variables and functions */
 unsigned long CLONE_NEWPID ; 
 int /*<<< orphan*/  EINVAL ; 
 struct pid_namespace* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct pid_namespace* create_pid_namespace (struct user_namespace*,struct pid_namespace*) ; 
 int /*<<< orphan*/  current ; 
 struct pid_namespace* get_pid_ns (struct pid_namespace*) ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 

struct pid_namespace *copy_pid_ns(unsigned long flags,
	struct user_namespace *user_ns, struct pid_namespace *old_ns)
{
	if (!(flags & CLONE_NEWPID))
		return get_pid_ns(old_ns);
	if (task_active_pid_ns(current) != old_ns)
		return ERR_PTR(-EINVAL);
	return create_pid_namespace(user_ns, old_ns);
}