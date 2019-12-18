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
struct smack_known {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 struct cred* __task_cred (struct task_struct const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smack_cred (struct cred const*) ; 
 struct smack_known* smk_of_task (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct smack_known *smk_of_task_struct(
						const struct task_struct *t)
{
	struct smack_known *skp;
	const struct cred *cred;

	rcu_read_lock();

	cred = __task_cred(t);
	skp = smk_of_task(smack_cred(cred));

	rcu_read_unlock();

	return skp;
}