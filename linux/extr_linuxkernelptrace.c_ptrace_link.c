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
 int /*<<< orphan*/  __ptrace_link (struct task_struct*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void ptrace_link(struct task_struct *child, struct task_struct *new_parent)
{
	rcu_read_lock();
	__ptrace_link(child, new_parent, __task_cred(new_parent));
	rcu_read_unlock();
}