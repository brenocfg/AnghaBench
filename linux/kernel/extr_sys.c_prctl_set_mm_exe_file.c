#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_1__* vm_file; struct vm_area_struct* vm_next; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  exe_file; struct vm_area_struct* mmap; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int /*<<< orphan*/  f_path; } ;
struct fd {TYPE_2__* file; } ;
struct TYPE_6__ {int /*<<< orphan*/  f_path; } ;
struct TYPE_5__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int EACCES ; 
 int EBADF ; 
 int EBUSY ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct fd fdget (unsigned int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 struct inode* file_inode (TYPE_2__*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  get_file (TYPE_2__*) ; 
 struct file* get_mm_exe_file (struct mm_struct*) ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ path_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ path_noexec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct file* xchg (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int prctl_set_mm_exe_file(struct mm_struct *mm, unsigned int fd)
{
	struct fd exe;
	struct file *old_exe, *exe_file;
	struct inode *inode;
	int err;

	exe = fdget(fd);
	if (!exe.file)
		return -EBADF;

	inode = file_inode(exe.file);

	/*
	 * Because the original mm->exe_file points to executable file, make
	 * sure that this one is executable as well, to avoid breaking an
	 * overall picture.
	 */
	err = -EACCES;
	if (!S_ISREG(inode->i_mode) || path_noexec(&exe.file->f_path))
		goto exit;

	err = inode_permission(inode, MAY_EXEC);
	if (err)
		goto exit;

	/*
	 * Forbid mm->exe_file change if old file still mapped.
	 */
	exe_file = get_mm_exe_file(mm);
	err = -EBUSY;
	if (exe_file) {
		struct vm_area_struct *vma;

		down_read(&mm->mmap_sem);
		for (vma = mm->mmap; vma; vma = vma->vm_next) {
			if (!vma->vm_file)
				continue;
			if (path_equal(&vma->vm_file->f_path,
				       &exe_file->f_path))
				goto exit_err;
		}

		up_read(&mm->mmap_sem);
		fput(exe_file);
	}

	err = 0;
	/* set the new file, lockless */
	get_file(exe.file);
	old_exe = xchg(&mm->exe_file, exe.file);
	if (old_exe)
		fput(old_exe);
exit:
	fdput(exe);
	return err;
exit_err:
	up_read(&mm->mmap_sem);
	fput(exe_file);
	goto exit;
}