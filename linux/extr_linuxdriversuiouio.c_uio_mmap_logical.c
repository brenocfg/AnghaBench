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

/* Variables and functions */
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int /*<<< orphan*/  uio_logical_vm_ops ; 

__attribute__((used)) static int uio_mmap_logical(struct vm_area_struct *vma)
{
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &uio_logical_vm_ops;
	return 0;
}