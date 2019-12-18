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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_MAYWRITE ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  sel_mmap_policy_ops ; 

__attribute__((used)) static int sel_mmap_policy(struct file *filp, struct vm_area_struct *vma)
{
	if (vma->vm_flags & VM_SHARED) {
		/* do not allow mprotect to make mapping writable */
		vma->vm_flags &= ~VM_MAYWRITE;

		if (vma->vm_flags & VM_WRITE)
			return -EACCES;
	}

	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &sel_mmap_policy_ops;

	return 0;
}