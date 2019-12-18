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
struct task_struct {struct kcov* kcov; } ;
struct kcov {int /*<<< orphan*/  lock; int /*<<< orphan*/  mode; struct task_struct* t; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCOV_MODE_INIT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kcov_put (struct kcov*) ; 
 int /*<<< orphan*/  kcov_task_init (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kcov_task_exit(struct task_struct *t)
{
	struct kcov *kcov;

	kcov = t->kcov;
	if (kcov == NULL)
		return;
	spin_lock(&kcov->lock);
	if (WARN_ON(kcov->t != t)) {
		spin_unlock(&kcov->lock);
		return;
	}
	/* Just to not leave dangling references behind. */
	kcov_task_init(t);
	kcov->t = NULL;
	kcov->mode = KCOV_MODE_INIT;
	spin_unlock(&kcov->lock);
	kcov_put(kcov);
}