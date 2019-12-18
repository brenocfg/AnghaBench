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
 int /*<<< orphan*/  CONFIG_UBIFS_ATIME_SUPPORT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  ubifs_file_vm_ops ; 

__attribute__((used)) static int ubifs_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	int err;

	err = generic_file_mmap(file, vma);
	if (err)
		return err;
	vma->vm_ops = &ubifs_file_vm_ops;

	if (IS_ENABLED(CONFIG_UBIFS_ATIME_SUPPORT))
		file_accessed(file);

	return 0;
}