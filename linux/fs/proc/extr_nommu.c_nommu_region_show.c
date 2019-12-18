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
struct vm_region {int vm_flags; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct file* vm_file; } ;
struct seq_file {int dummy; } ;
struct inode {unsigned long i_ino; TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int VM_EXEC ; 
 int VM_MAYSHARE ; 
 int VM_READ ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  seq_file_path (struct seq_file*,struct file*,char*) ; 
 int /*<<< orphan*/  seq_pad (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,char,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_setwidth (struct seq_file*,int) ; 

__attribute__((used)) static int nommu_region_show(struct seq_file *m, struct vm_region *region)
{
	unsigned long ino = 0;
	struct file *file;
	dev_t dev = 0;
	int flags;

	flags = region->vm_flags;
	file = region->vm_file;

	if (file) {
		struct inode *inode = file_inode(region->vm_file);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
	}

	seq_setwidth(m, 25 + sizeof(void *) * 6 - 1);
	seq_printf(m,
		   "%08lx-%08lx %c%c%c%c %08llx %02x:%02x %lu ",
		   region->vm_start,
		   region->vm_end,
		   flags & VM_READ ? 'r' : '-',
		   flags & VM_WRITE ? 'w' : '-',
		   flags & VM_EXEC ? 'x' : '-',
		   flags & VM_MAYSHARE ? flags & VM_SHARED ? 'S' : 's' : 'p',
		   ((loff_t)region->vm_pgoff) << PAGE_SHIFT,
		   MAJOR(dev), MINOR(dev), ino);

	if (file) {
		seq_pad(m, ' ');
		seq_file_path(m, file, "");
	}

	seq_putc(m, '\n');
	return 0;
}