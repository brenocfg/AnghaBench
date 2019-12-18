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
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct task_struct {int dummy; } ;
struct path {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct path f_path; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int dname_to_vma_addr (struct dentry*,unsigned long*,unsigned long*) ; 
 int down_read_killable (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_exact_vma (struct mm_struct*,unsigned long,unsigned long) ; 
 struct task_struct* get_proc_task (int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int map_files_get_link(struct dentry *dentry, struct path *path)
{
	unsigned long vm_start, vm_end;
	struct vm_area_struct *vma;
	struct task_struct *task;
	struct mm_struct *mm;
	int rc;

	rc = -ENOENT;
	task = get_proc_task(d_inode(dentry));
	if (!task)
		goto out;

	mm = get_task_mm(task);
	put_task_struct(task);
	if (!mm)
		goto out;

	rc = dname_to_vma_addr(dentry, &vm_start, &vm_end);
	if (rc)
		goto out_mmput;

	rc = down_read_killable(&mm->mmap_sem);
	if (rc)
		goto out_mmput;

	rc = -ENOENT;
	vma = find_exact_vma(mm, vm_start, vm_end);
	if (vma && vma->vm_file) {
		*path = vma->vm_file->f_path;
		path_get(path);
		rc = 0;
	}
	up_read(&mm->mmap_sem);

out_mmput:
	mmput(mm);
out:
	return rc;
}