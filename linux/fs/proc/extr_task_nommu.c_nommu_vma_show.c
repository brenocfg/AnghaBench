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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; scalar_t__ vm_pgoff; struct file* vm_file; struct mm_struct* vm_mm; } ;
struct seq_file {int dummy; } ;
struct mm_struct {int dummy; } ;
struct inode {unsigned long i_ino; TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
typedef  unsigned long long loff_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 unsigned long long PAGE_SHIFT ; 
 int VM_EXEC ; 
 int VM_MAYSHARE ; 
 int VM_READ ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ is_stack (struct vm_area_struct*) ; 
 int /*<<< orphan*/  seq_file_path (struct seq_file*,struct file*,char*) ; 
 int /*<<< orphan*/  seq_pad (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,char,char,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  seq_setwidth (struct seq_file*,int) ; 

__attribute__((used)) static int nommu_vma_show(struct seq_file *m, struct vm_area_struct *vma)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long ino = 0;
	struct file *file;
	dev_t dev = 0;
	int flags;
	unsigned long long pgoff = 0;

	flags = vma->vm_flags;
	file = vma->vm_file;

	if (file) {
		struct inode *inode = file_inode(vma->vm_file);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		pgoff = (loff_t)vma->vm_pgoff << PAGE_SHIFT;
	}

	seq_setwidth(m, 25 + sizeof(void *) * 6 - 1);
	seq_printf(m,
		   "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %lu ",
		   vma->vm_start,
		   vma->vm_end,
		   flags & VM_READ ? 'r' : '-',
		   flags & VM_WRITE ? 'w' : '-',
		   flags & VM_EXEC ? 'x' : '-',
		   flags & VM_MAYSHARE ? flags & VM_SHARED ? 'S' : 's' : 'p',
		   pgoff,
		   MAJOR(dev), MINOR(dev), ino);

	if (file) {
		seq_pad(m, ' ');
		seq_file_path(m, file, "");
	} else if (mm && is_stack(vma)) {
		seq_pad(m, ' ');
		seq_puts(m, "[stack]");
	}

	seq_putc(m, '\n');
	return 0;
}