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
struct mm_struct {TYPE_1__* binfmt; int /*<<< orphan*/  total_vm; int /*<<< orphan*/  hiwater_vm; int /*<<< orphan*/  hiwater_rss; int /*<<< orphan*/  user_ns; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 struct mm_struct* allocate_mm () ; 
 int dup_mmap (struct mm_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  get_mm_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  memcpy (struct mm_struct*,struct mm_struct*,int) ; 
 int /*<<< orphan*/  mm_init (struct mm_struct*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_init_owner (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mm_struct *dup_mm(struct task_struct *tsk,
				struct mm_struct *oldmm)
{
	struct mm_struct *mm;
	int err;

	mm = allocate_mm();
	if (!mm)
		goto fail_nomem;

	memcpy(mm, oldmm, sizeof(*mm));

	if (!mm_init(mm, tsk, mm->user_ns))
		goto fail_nomem;

	err = dup_mmap(mm, oldmm);
	if (err)
		goto free_pt;

	mm->hiwater_rss = get_mm_rss(mm);
	mm->hiwater_vm = mm->total_vm;

	if (mm->binfmt && !try_module_get(mm->binfmt->module))
		goto free_pt;

	return mm;

free_pt:
	/* don't put binfmt in mmput, we haven't got module yet */
	mm->binfmt = NULL;
	mm_init_owner(mm, NULL);
	mmput(mm);

fail_nomem:
	return NULL;
}