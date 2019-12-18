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
struct ns_common {int dummy; } ;
struct user_namespace {struct ns_common ns; } ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 TYPE_1__* __task_cred (struct task_struct*) ; 
 struct user_namespace* get_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct ns_common *userns_get(struct task_struct *task)
{
	struct user_namespace *user_ns;

	rcu_read_lock();
	user_ns = get_user_ns(__task_cred(task)->user_ns);
	rcu_read_unlock();

	return user_ns ? &user_ns->ns : NULL;
}