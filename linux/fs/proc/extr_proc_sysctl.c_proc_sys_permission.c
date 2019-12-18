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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct ctl_table_header {int dummy; } ;
struct ctl_table {int dummy; } ;
struct TYPE_2__ {struct ctl_table* sysctl_entry; } ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ IS_ERR (struct ctl_table_header*) ; 
 int MAY_EXEC ; 
 int MAY_NOT_BLOCK ; 
 int MAY_WRITE ; 
 TYPE_1__* PROC_I (struct inode*) ; 
 int PTR_ERR (struct ctl_table_header*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct ctl_table_header* grab_header (struct inode*) ; 
 int /*<<< orphan*/  sysctl_head_finish (struct ctl_table_header*) ; 
 int sysctl_perm (struct ctl_table_header*,struct ctl_table*,int) ; 

__attribute__((used)) static int proc_sys_permission(struct inode *inode, int mask)
{
	/*
	 * sysctl entries that are not writeable,
	 * are _NOT_ writeable, capabilities or not.
	 */
	struct ctl_table_header *head;
	struct ctl_table *table;
	int error;

	/* Executable files are not allowed under /proc/sys/ */
	if ((mask & MAY_EXEC) && S_ISREG(inode->i_mode))
		return -EACCES;

	head = grab_header(inode);
	if (IS_ERR(head))
		return PTR_ERR(head);

	table = PROC_I(inode)->sysctl_entry;
	if (!table) /* global root - r-xr-xr-x */
		error = mask & MAY_WRITE ? -EACCES : 0;
	else /* Use the permissions on the sysctl table entry */
		error = sysctl_perm(head, table, mask & ~MAY_NOT_BLOCK);

	sysctl_head_finish(head);
	return error;
}