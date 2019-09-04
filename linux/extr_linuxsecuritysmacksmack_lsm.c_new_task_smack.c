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
struct task_smack {int /*<<< orphan*/  smk_rules_lock; int /*<<< orphan*/  smk_relabel; int /*<<< orphan*/  smk_rules; struct smack_known* smk_forked; struct smack_known* smk_task; } ;
struct smack_known {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct task_smack* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct task_smack *new_task_smack(struct smack_known *task,
					struct smack_known *forked, gfp_t gfp)
{
	struct task_smack *tsp;

	tsp = kzalloc(sizeof(struct task_smack), gfp);
	if (tsp == NULL)
		return NULL;

	tsp->smk_task = task;
	tsp->smk_forked = forked;
	INIT_LIST_HEAD(&tsp->smk_rules);
	INIT_LIST_HEAD(&tsp->smk_relabel);
	mutex_init(&tsp->smk_rules_lock);

	return tsp;
}