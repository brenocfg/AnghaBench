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
struct qstr {unsigned int len; int /*<<< orphan*/  name; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct ctl_table_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sysctl; } ;

/* Variables and functions */
 TYPE_1__* PROC_I (struct inode*) ; 
 struct inode* d_inode_rcu (struct dentry const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 struct ctl_table_header* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_is_seen (struct ctl_table_header*) ; 

__attribute__((used)) static int proc_sys_compare(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	struct ctl_table_header *head;
	struct inode *inode;

	/* Although proc doesn't have negative dentries, rcu-walk means
	 * that inode here can be NULL */
	/* AV: can it, indeed? */
	inode = d_inode_rcu(dentry);
	if (!inode)
		return 1;
	if (name->len != len)
		return 1;
	if (memcmp(name->name, str, len))
		return 1;
	head = rcu_dereference(PROC_I(inode)->sysctl);
	return !head || !sysctl_is_seen(head);
}