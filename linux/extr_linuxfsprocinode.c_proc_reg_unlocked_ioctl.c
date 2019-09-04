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
struct proc_dir_entry {TYPE_1__* proc_fops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {long (* unlocked_ioctl ) (struct file*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTTY ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  unuse_pde (struct proc_dir_entry*) ; 
 scalar_t__ use_pde (struct proc_dir_entry*) ; 

__attribute__((used)) static long proc_reg_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct proc_dir_entry *pde = PDE(file_inode(file));
	long rv = -ENOTTY;
	long (*ioctl)(struct file *, unsigned int, unsigned long);
	if (use_pde(pde)) {
		ioctl = pde->proc_fops->unlocked_ioctl;
		if (ioctl)
			rv = ioctl(file, cmd, arg);
		unuse_pde(pde);
	}
	return rv;
}