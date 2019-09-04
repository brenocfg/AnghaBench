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
struct vm_area_struct {int dummy; } ;
struct file {TYPE_1__* f_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int ENODEV ; 
 struct file* ecryptfs_file_to_lower (struct file*) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 

__attribute__((used)) static int ecryptfs_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct file *lower_file = ecryptfs_file_to_lower(file);
	/*
	 * Don't allow mmap on top of file systems that don't support it
	 * natively.  If FILESYSTEM_MAX_STACK_DEPTH > 2 or ecryptfs
	 * allows recursive mounting, this will need to be extended.
	 */
	if (!lower_file->f_op->mmap)
		return -ENODEV;
	return generic_file_mmap(file, vma);
}