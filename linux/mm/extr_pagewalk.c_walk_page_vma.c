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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; TYPE_1__* vm_mm; } ;
struct mm_walk_ops {int dummy; } ;
struct mm_walk {void* private; TYPE_1__* mm; struct vm_area_struct* vma; struct mm_walk_ops const* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int __walk_page_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_walk*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int walk_page_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_walk*) ; 

int walk_page_vma(struct vm_area_struct *vma, const struct mm_walk_ops *ops,
		void *private)
{
	struct mm_walk walk = {
		.ops		= ops,
		.mm		= vma->vm_mm,
		.vma		= vma,
		.private	= private,
	};
	int err;

	if (!walk.mm)
		return -EINVAL;

	lockdep_assert_held(&walk.mm->mmap_sem);

	err = walk_page_test(vma->vm_start, vma->vm_end, &walk);
	if (err > 0)
		return 0;
	if (err < 0)
		return err;
	return __walk_page_range(vma->vm_start, vma->vm_end, &walk);
}