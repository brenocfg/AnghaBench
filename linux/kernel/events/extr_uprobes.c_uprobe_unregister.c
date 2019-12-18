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
struct uprobe_consumer {int dummy; } ;
struct uprobe {int /*<<< orphan*/  register_rwsem; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __uprobe_unregister (struct uprobe*,struct uprobe_consumer*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct uprobe* find_uprobe (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_uprobe (struct uprobe*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void uprobe_unregister(struct inode *inode, loff_t offset, struct uprobe_consumer *uc)
{
	struct uprobe *uprobe;

	uprobe = find_uprobe(inode, offset);
	if (WARN_ON(!uprobe))
		return;

	down_write(&uprobe->register_rwsem);
	__uprobe_unregister(uprobe, uc);
	up_write(&uprobe->register_rwsem);
	put_uprobe(uprobe);
}