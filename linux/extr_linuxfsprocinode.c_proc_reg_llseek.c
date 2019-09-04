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
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* llseek ) (struct file*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  unuse_pde (struct proc_dir_entry*) ; 
 scalar_t__ use_pde (struct proc_dir_entry*) ; 

__attribute__((used)) static loff_t proc_reg_llseek(struct file *file, loff_t offset, int whence)
{
	struct proc_dir_entry *pde = PDE(file_inode(file));
	loff_t rv = -EINVAL;
	if (use_pde(pde)) {
		loff_t (*llseek)(struct file *, loff_t, int);
		llseek = pde->proc_fops->llseek;
		if (!llseek)
			llseek = default_llseek;
		rv = llseek(file, offset, whence);
		unuse_pde(pde);
	}
	return rv;
}