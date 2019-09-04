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
struct proc_dir_entry {TYPE_1__* proc_fops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* mmap ) (struct file*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  unuse_pde (struct proc_dir_entry*) ; 
 scalar_t__ use_pde (struct proc_dir_entry*) ; 

__attribute__((used)) static int proc_reg_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct proc_dir_entry *pde = PDE(file_inode(file));
	int rv = -EIO;
	int (*mmap)(struct file *, struct vm_area_struct *);
	if (use_pde(pde)) {
		mmap = pde->proc_fops->mmap;
		if (mmap)
			rv = mmap(file, vma);
		unuse_pde(pde);
	}
	return rv;
}