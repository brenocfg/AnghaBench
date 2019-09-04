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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  v9fs_file_vm_ops ; 

__attribute__((used)) static int
v9fs_file_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int retval;


	retval = generic_file_mmap(filp, vma);
	if (!retval)
		vma->vm_ops = &v9fs_file_vm_ops;

	return retval;
}