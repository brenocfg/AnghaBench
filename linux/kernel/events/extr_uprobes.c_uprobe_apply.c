#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uprobe_consumer {struct uprobe_consumer* next; } ;
struct uprobe {int /*<<< orphan*/  register_rwsem; struct uprobe_consumer* consumers; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct uprobe* find_uprobe (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_uprobe (struct uprobe*) ; 
 int register_for_each_vma (struct uprobe*,struct uprobe_consumer*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int uprobe_apply(struct inode *inode, loff_t offset,
			struct uprobe_consumer *uc, bool add)
{
	struct uprobe *uprobe;
	struct uprobe_consumer *con;
	int ret = -ENOENT;

	uprobe = find_uprobe(inode, offset);
	if (WARN_ON(!uprobe))
		return ret;

	down_write(&uprobe->register_rwsem);
	for (con = uprobe->consumers; con && con != uc ; con = con->next)
		;
	if (con)
		ret = register_for_each_vma(uprobe, add ? uc : NULL);
	up_write(&uprobe->register_rwsem);
	put_uprobe(uprobe);

	return ret;
}