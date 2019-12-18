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
struct mmu_notifier_ops {int /*<<< orphan*/  (* free_notifier ) (struct mmu_notifier*) ;struct mmu_notifier* (* alloc_notifier ) (struct mm_struct*) ;} ;
struct mmu_notifier {struct mmu_notifier_ops const* ops; } ;
struct mm_struct {scalar_t__ mmu_notifier_mm; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 struct mmu_notifier* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mmu_notifier*) ; 
 int __mmu_notifier_register (struct mmu_notifier*,struct mm_struct*) ; 
 struct mmu_notifier* find_get_mmu_notifier (struct mm_struct*,struct mmu_notifier_ops const*) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 struct mmu_notifier* stub1 (struct mm_struct*) ; 
 int /*<<< orphan*/  stub2 (struct mmu_notifier*) ; 

struct mmu_notifier *mmu_notifier_get_locked(const struct mmu_notifier_ops *ops,
					     struct mm_struct *mm)
{
	struct mmu_notifier *mn;
	int ret;

	lockdep_assert_held_write(&mm->mmap_sem);

	if (mm->mmu_notifier_mm) {
		mn = find_get_mmu_notifier(mm, ops);
		if (mn)
			return mn;
	}

	mn = ops->alloc_notifier(mm);
	if (IS_ERR(mn))
		return mn;
	mn->ops = ops;
	ret = __mmu_notifier_register(mn, mm);
	if (ret)
		goto out_free;
	return mn;
out_free:
	mn->ops->free_notifier(mn);
	return ERR_PTR(ret);
}