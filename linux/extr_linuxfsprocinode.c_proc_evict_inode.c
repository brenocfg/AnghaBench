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
struct proc_dir_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_data; } ;
struct ctl_table_header {int dummy; } ;
struct TYPE_2__ {struct ctl_table_header* sysctl; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 
 TYPE_1__* PROC_I (struct inode*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct ctl_table_header*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  pde_put (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_sys_evict_inode (struct inode*,struct ctl_table_header*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void proc_evict_inode(struct inode *inode)
{
	struct proc_dir_entry *de;
	struct ctl_table_header *head;

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);

	/* Stop tracking associated processes */
	put_pid(PROC_I(inode)->pid);

	/* Let go of any associated proc directory entry */
	de = PDE(inode);
	if (de)
		pde_put(de);

	head = PROC_I(inode)->sysctl;
	if (head) {
		RCU_INIT_POINTER(PROC_I(inode)->sysctl, NULL);
		proc_sys_evict_inode(inode, head);
	}
}