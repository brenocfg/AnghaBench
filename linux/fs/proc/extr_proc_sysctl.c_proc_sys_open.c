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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct ctl_table_header {int dummy; } ;
struct ctl_table {scalar_t__ poll; } ;
struct TYPE_2__ {struct ctl_table* sysctl_entry; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ctl_table_header*) ; 
 TYPE_1__* PROC_I (struct inode*) ; 
 int PTR_ERR (struct ctl_table_header*) ; 
 struct ctl_table_header* grab_header (struct inode*) ; 
 int /*<<< orphan*/  proc_sys_poll_event (scalar_t__) ; 
 int /*<<< orphan*/  sysctl_head_finish (struct ctl_table_header*) ; 

__attribute__((used)) static int proc_sys_open(struct inode *inode, struct file *filp)
{
	struct ctl_table_header *head = grab_header(inode);
	struct ctl_table *table = PROC_I(inode)->sysctl_entry;

	/* sysctl was unregistered */
	if (IS_ERR(head))
		return PTR_ERR(head);

	if (table->poll)
		filp->private_data = proc_sys_poll_event(table->poll);

	sysctl_head_finish(head);

	return 0;
}