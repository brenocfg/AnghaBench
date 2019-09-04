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
struct vm_area_struct {TYPE_1__* vm_file; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct vm_area_struct* vm_next; } ;
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;
struct map_files_info {scalar_t__ mode; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct flex_array {int dummy; } ;
struct file {int dummy; } ;
struct dir_context {unsigned long pos; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EACCES ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PTRACE_MODE_READ_FSCREDS ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct flex_array* flex_array_alloc (int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flex_array_free (struct flex_array*) ; 
 struct map_files_info* flex_array_get (struct flex_array*,unsigned long) ; 
 scalar_t__ flex_array_prealloc (struct flex_array*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ flex_array_put (struct flex_array*,int /*<<< orphan*/ ,struct map_files_info*,int /*<<< orphan*/ ) ; 
 struct task_struct* get_proc_task (int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  proc_fill_cache (struct file*,struct dir_context*,char*,unsigned int,int /*<<< orphan*/ ,struct task_struct*,void*) ; 
 int /*<<< orphan*/  proc_map_files_instantiate ; 
 int /*<<< orphan*/  ptrace_may_access (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 unsigned int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
proc_map_files_readdir(struct file *file, struct dir_context *ctx)
{
	struct vm_area_struct *vma;
	struct task_struct *task;
	struct mm_struct *mm;
	unsigned long nr_files, pos, i;
	struct flex_array *fa = NULL;
	struct map_files_info info;
	struct map_files_info *p;
	int ret;

	ret = -ENOENT;
	task = get_proc_task(file_inode(file));
	if (!task)
		goto out;

	ret = -EACCES;
	if (!ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS))
		goto out_put_task;

	ret = 0;
	if (!dir_emit_dots(file, ctx))
		goto out_put_task;

	mm = get_task_mm(task);
	if (!mm)
		goto out_put_task;
	down_read(&mm->mmap_sem);

	nr_files = 0;

	/*
	 * We need two passes here:
	 *
	 *  1) Collect vmas of mapped files with mmap_sem taken
	 *  2) Release mmap_sem and instantiate entries
	 *
	 * otherwise we get lockdep complained, since filldir()
	 * routine might require mmap_sem taken in might_fault().
	 */

	for (vma = mm->mmap, pos = 2; vma; vma = vma->vm_next) {
		if (vma->vm_file && ++pos > ctx->pos)
			nr_files++;
	}

	if (nr_files) {
		fa = flex_array_alloc(sizeof(info), nr_files,
					GFP_KERNEL);
		if (!fa || flex_array_prealloc(fa, 0, nr_files,
						GFP_KERNEL)) {
			ret = -ENOMEM;
			if (fa)
				flex_array_free(fa);
			up_read(&mm->mmap_sem);
			mmput(mm);
			goto out_put_task;
		}
		for (i = 0, vma = mm->mmap, pos = 2; vma;
				vma = vma->vm_next) {
			if (!vma->vm_file)
				continue;
			if (++pos <= ctx->pos)
				continue;

			info.start = vma->vm_start;
			info.end = vma->vm_end;
			info.mode = vma->vm_file->f_mode;
			if (flex_array_put(fa, i++, &info, GFP_KERNEL))
				BUG();
		}
	}
	up_read(&mm->mmap_sem);
	mmput(mm);

	for (i = 0; i < nr_files; i++) {
		char buf[4 * sizeof(long) + 2];	/* max: %lx-%lx\0 */
		unsigned int len;

		p = flex_array_get(fa, i);
		len = snprintf(buf, sizeof(buf), "%lx-%lx", p->start, p->end);
		if (!proc_fill_cache(file, ctx,
				      buf, len,
				      proc_map_files_instantiate,
				      task,
				      (void *)(unsigned long)p->mode))
			break;
		ctx->pos++;
	}
	if (fa)
		flex_array_free(fa);

out_put_task:
	put_task_struct(task);
out:
	return ret;
}