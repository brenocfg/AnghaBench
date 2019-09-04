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
struct task_struct {int dummy; } ;
struct smack_known {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  security; } ;

/* Variables and functions */
 TYPE_1__* __task_cred (struct task_struct const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct smack_known* smk_of_task (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct smack_known *smk_of_task_struct(const struct task_struct *t)
{
	struct smack_known *skp;

	rcu_read_lock();
	skp = smk_of_task(__task_cred(t)->security);
	rcu_read_unlock();
	return skp;
}