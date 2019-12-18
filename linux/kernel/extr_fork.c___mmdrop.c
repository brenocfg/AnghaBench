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
struct mm_struct {int /*<<< orphan*/  user_ns; } ;
struct TYPE_2__ {struct mm_struct* active_mm; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  check_mm (struct mm_struct*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  destroy_context (struct mm_struct*) ; 
 int /*<<< orphan*/  free_mm (struct mm_struct*) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  mm_free_pgd (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_mm_destroy (struct mm_struct*) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 

void __mmdrop(struct mm_struct *mm)
{
	BUG_ON(mm == &init_mm);
	WARN_ON_ONCE(mm == current->mm);
	WARN_ON_ONCE(mm == current->active_mm);
	mm_free_pgd(mm);
	destroy_context(mm);
	mmu_notifier_mm_destroy(mm);
	check_mm(mm);
	put_user_ns(mm->user_ns);
	free_mm(mm);
}