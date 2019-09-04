#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {struct file* vm_file; } ;
struct file {TYPE_1__* f_op; struct file* private_data; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 int call_mmap (struct file*,struct vm_area_struct*) ; 
 TYPE_2__* file_inode (struct file*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_file (struct file*) ; 
 int /*<<< orphan*/  ovl_file_accessed (struct file*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

__attribute__((used)) static int ovl_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct file *realfile = file->private_data;
	const struct cred *old_cred;
	int ret;

	if (!realfile->f_op->mmap)
		return -ENODEV;

	if (WARN_ON(file != vma->vm_file))
		return -EIO;

	vma->vm_file = get_file(realfile);

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	ret = call_mmap(vma->vm_file, vma);
	revert_creds(old_cred);

	if (ret) {
		/* Drop reference count from new vm_file value */
		fput(realfile);
	} else {
		/* Drop reference count from previous vm_file value */
		fput(file);
	}

	ovl_file_accessed(file);

	return ret;
}