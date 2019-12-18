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
typedef  int /*<<< orphan*/  vm_flags_t ;
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; TYPE_2__* vm_ops; scalar_t__ vm_pgoff; struct file* vm_file; int /*<<< orphan*/  vm_flags; struct mm_struct* vm_mm; } ;
struct seq_file {int dummy; } ;
struct mm_struct {unsigned long brk; unsigned long start_brk; } ;
struct inode {unsigned long i_ino; TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
typedef  unsigned long long loff_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {char* (* name ) (struct vm_area_struct*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 unsigned long long PAGE_SHIFT ; 
 char* arch_vma_name (struct vm_area_struct*) ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ is_stack (struct vm_area_struct*) ; 
 int /*<<< orphan*/  seq_file_path (struct seq_file*,struct file*,char*) ; 
 int /*<<< orphan*/  seq_pad (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char const*) ; 
 int /*<<< orphan*/  show_vma_header_prefix (struct seq_file*,unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,unsigned long) ; 
 char* stub1 (struct vm_area_struct*) ; 

__attribute__((used)) static void
show_map_vma(struct seq_file *m, struct vm_area_struct *vma)
{
	struct mm_struct *mm = vma->vm_mm;
	struct file *file = vma->vm_file;
	vm_flags_t flags = vma->vm_flags;
	unsigned long ino = 0;
	unsigned long long pgoff = 0;
	unsigned long start, end;
	dev_t dev = 0;
	const char *name = NULL;

	if (file) {
		struct inode *inode = file_inode(vma->vm_file);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		pgoff = ((loff_t)vma->vm_pgoff) << PAGE_SHIFT;
	}

	start = vma->vm_start;
	end = vma->vm_end;
	show_vma_header_prefix(m, start, end, flags, pgoff, dev, ino);

	/*
	 * Print the dentry name for named mappings, and a
	 * special [heap] marker for the heap:
	 */
	if (file) {
		seq_pad(m, ' ');
		seq_file_path(m, file, "\n");
		goto done;
	}

	if (vma->vm_ops && vma->vm_ops->name) {
		name = vma->vm_ops->name(vma);
		if (name)
			goto done;
	}

	name = arch_vma_name(vma);
	if (!name) {
		if (!mm) {
			name = "[vdso]";
			goto done;
		}

		if (vma->vm_start <= mm->brk &&
		    vma->vm_end >= mm->start_brk) {
			name = "[heap]";
			goto done;
		}

		if (is_stack(vma))
			name = "[stack]";
	}

done:
	if (name) {
		seq_pad(m, ' ');
		seq_puts(m, name);
	}
	seq_putc(m, '\n');
}