#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int dummy; } ;
struct linux_binprm {struct mm_struct* mm; int /*<<< orphan*/  rlim_stack; } ;
struct TYPE_4__ {int /*<<< orphan*/  group_leader; TYPE_1__* signal; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rlim; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t RLIMIT_STACK ; 
 int __bprm_mm_init (struct linux_binprm*) ; 
 TYPE_2__* current ; 
 struct mm_struct* mm_alloc () ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bprm_mm_init(struct linux_binprm *bprm)
{
	int err;
	struct mm_struct *mm = NULL;

	bprm->mm = mm = mm_alloc();
	err = -ENOMEM;
	if (!mm)
		goto err;

	/* Save current stack limit for all calculations made during exec. */
	task_lock(current->group_leader);
	bprm->rlim_stack = current->signal->rlim[RLIMIT_STACK];
	task_unlock(current->group_leader);

	err = __bprm_mm_init(bprm);
	if (err)
		goto err;

	return 0;

err:
	if (mm) {
		bprm->mm = NULL;
		mmdrop(mm);
	}

	return err;
}