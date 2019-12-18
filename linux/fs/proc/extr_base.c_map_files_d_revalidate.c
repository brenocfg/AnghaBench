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
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 scalar_t__ IS_ERR_OR_NULL (struct mm_struct*) ; 
 unsigned int LOOKUP_RCU ; 
 int /*<<< orphan*/  PTRACE_MODE_READ_FSCREDS ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dname_to_vma_addr (struct dentry*,unsigned long*,unsigned long*) ; 
 int down_read_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_exact_vma (struct mm_struct*,unsigned long,unsigned long) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 struct mm_struct* mm_access (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  security_task_to_inode (struct task_struct*,struct inode*) ; 
 int /*<<< orphan*/  task_dump_owner (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int map_files_d_revalidate(struct dentry *dentry, unsigned int flags)
{
	unsigned long vm_start, vm_end;
	bool exact_vma_exists = false;
	struct mm_struct *mm = NULL;
	struct task_struct *task;
	struct inode *inode;
	int status = 0;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	inode = d_inode(dentry);
	task = get_proc_task(inode);
	if (!task)
		goto out_notask;

	mm = mm_access(task, PTRACE_MODE_READ_FSCREDS);
	if (IS_ERR_OR_NULL(mm))
		goto out;

	if (!dname_to_vma_addr(dentry, &vm_start, &vm_end)) {
		status = down_read_killable(&mm->mmap_sem);
		if (!status) {
			exact_vma_exists = !!find_exact_vma(mm, vm_start,
							    vm_end);
			up_read(&mm->mmap_sem);
		}
	}

	mmput(mm);

	if (exact_vma_exists) {
		task_dump_owner(task, 0, &inode->i_uid, &inode->i_gid);

		security_task_to_inode(task, inode);
		status = 1;
	}

out:
	put_task_struct(task);

out_notask:
	return status;
}