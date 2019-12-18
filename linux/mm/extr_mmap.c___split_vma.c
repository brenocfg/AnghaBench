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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; scalar_t__ vm_file; TYPE_1__* vm_ops; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {int (* split ) (struct vm_area_struct*,unsigned long) ;int /*<<< orphan*/  (* close ) (struct vm_area_struct*) ;int /*<<< orphan*/  (* open ) (struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int anon_vma_clone (struct vm_area_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  get_file (scalar_t__) ; 
 int /*<<< orphan*/  mpol_put (int /*<<< orphan*/ ) ; 
 int stub1 (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct vm_area_struct*) ; 
 int /*<<< orphan*/  stub3 (struct vm_area_struct*) ; 
 int /*<<< orphan*/  unlink_anon_vmas (struct vm_area_struct*) ; 
 struct vm_area_struct* vm_area_dup (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vm_area_free (struct vm_area_struct*) ; 
 int vma_adjust (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,struct vm_area_struct*) ; 
 int vma_dup_policy (struct vm_area_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 

int __split_vma(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long addr, int new_below)
{
	struct vm_area_struct *new;
	int err;

	if (vma->vm_ops && vma->vm_ops->split) {
		err = vma->vm_ops->split(vma, addr);
		if (err)
			return err;
	}

	new = vm_area_dup(vma);
	if (!new)
		return -ENOMEM;

	if (new_below)
		new->vm_end = addr;
	else {
		new->vm_start = addr;
		new->vm_pgoff += ((addr - vma->vm_start) >> PAGE_SHIFT);
	}

	err = vma_dup_policy(vma, new);
	if (err)
		goto out_free_vma;

	err = anon_vma_clone(new, vma);
	if (err)
		goto out_free_mpol;

	if (new->vm_file)
		get_file(new->vm_file);

	if (new->vm_ops && new->vm_ops->open)
		new->vm_ops->open(new);

	if (new_below)
		err = vma_adjust(vma, addr, vma->vm_end, vma->vm_pgoff +
			((addr - new->vm_start) >> PAGE_SHIFT), new);
	else
		err = vma_adjust(vma, vma->vm_start, addr, vma->vm_pgoff, new);

	/* Success. */
	if (!err)
		return 0;

	/* Clean everything up if vma_adjust failed. */
	if (new->vm_ops && new->vm_ops->close)
		new->vm_ops->close(new);
	if (new->vm_file)
		fput(new->vm_file);
	unlink_anon_vmas(new);
 out_free_mpol:
	mpol_put(vma_policy(new));
 out_free_vma:
	vm_area_free(new);
	return err;
}