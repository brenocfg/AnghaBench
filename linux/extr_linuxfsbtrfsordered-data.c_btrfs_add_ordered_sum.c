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
struct btrfs_ordered_sum {int /*<<< orphan*/  list; } ;
struct btrfs_ordered_inode_tree {int /*<<< orphan*/  lock; } ;
struct btrfs_ordered_extent {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct btrfs_ordered_inode_tree ordered_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void btrfs_add_ordered_sum(struct inode *inode,
			   struct btrfs_ordered_extent *entry,
			   struct btrfs_ordered_sum *sum)
{
	struct btrfs_ordered_inode_tree *tree;

	tree = &BTRFS_I(inode)->ordered_tree;
	spin_lock_irq(&tree->lock);
	list_add_tail(&sum->list, &entry->list);
	spin_unlock_irq(&tree->lock);
}