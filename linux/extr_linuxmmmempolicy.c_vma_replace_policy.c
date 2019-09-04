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
struct vm_area_struct {struct mempolicy* vm_policy; TYPE_1__* vm_ops; int /*<<< orphan*/  vm_file; int /*<<< orphan*/  vm_pgoff; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct mempolicy {int dummy; } ;
struct TYPE_2__ {int (* set_policy ) (struct vm_area_struct*,struct mempolicy*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 int PTR_ERR (struct mempolicy*) ; 
 struct mempolicy* mpol_dup (struct mempolicy*) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int (*) (struct vm_area_struct*,struct mempolicy*)) ; 
 int stub1 (struct vm_area_struct*,struct mempolicy*) ; 

__attribute__((used)) static int vma_replace_policy(struct vm_area_struct *vma,
						struct mempolicy *pol)
{
	int err;
	struct mempolicy *old;
	struct mempolicy *new;

	pr_debug("vma %lx-%lx/%lx vm_ops %p vm_file %p set_policy %p\n",
		 vma->vm_start, vma->vm_end, vma->vm_pgoff,
		 vma->vm_ops, vma->vm_file,
		 vma->vm_ops ? vma->vm_ops->set_policy : NULL);

	new = mpol_dup(pol);
	if (IS_ERR(new))
		return PTR_ERR(new);

	if (vma->vm_ops && vma->vm_ops->set_policy) {
		err = vma->vm_ops->set_policy(vma, new);
		if (err)
			goto err_out;
	}

	old = vma->vm_policy;
	vma->vm_policy = new; /* protected by mmap_sem */
	mpol_put(old);

	return 0;
 err_out:
	mpol_put(new);
	return err;
}