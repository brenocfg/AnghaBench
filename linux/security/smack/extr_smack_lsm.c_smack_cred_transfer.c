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
struct task_smack {int /*<<< orphan*/  smk_rules; int /*<<< orphan*/  smk_rules_lock; int /*<<< orphan*/  smk_task; int /*<<< orphan*/  smk_forked; } ;
typedef  struct cred const cred ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct task_smack* smack_cred (struct cred const*) ; 

__attribute__((used)) static void smack_cred_transfer(struct cred *new, const struct cred *old)
{
	struct task_smack *old_tsp = smack_cred(old);
	struct task_smack *new_tsp = smack_cred(new);

	new_tsp->smk_task = old_tsp->smk_task;
	new_tsp->smk_forked = old_tsp->smk_task;
	mutex_init(&new_tsp->smk_rules_lock);
	INIT_LIST_HEAD(&new_tsp->smk_rules);

	/* cbs copy rule list */
}