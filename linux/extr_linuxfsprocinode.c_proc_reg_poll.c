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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* poll ) (struct file*,struct poll_table_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_POLLMASK ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  unuse_pde (struct proc_dir_entry*) ; 
 scalar_t__ use_pde (struct proc_dir_entry*) ; 

__attribute__((used)) static __poll_t proc_reg_poll(struct file *file, struct poll_table_struct *pts)
{
	struct proc_dir_entry *pde = PDE(file_inode(file));
	__poll_t rv = DEFAULT_POLLMASK;
	__poll_t (*poll)(struct file *, struct poll_table_struct *);
	if (use_pde(pde)) {
		poll = pde->proc_fops->poll;
		if (poll)
			rv = poll(file, pts);
		unuse_pde(pde);
	}
	return rv;
}