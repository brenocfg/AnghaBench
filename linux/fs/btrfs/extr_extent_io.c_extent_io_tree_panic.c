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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_io_tree {struct inode* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_panic (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  btrfs_sb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void extent_io_tree_panic(struct extent_io_tree *tree, int err)
{
	struct inode *inode = tree->private_data;

	btrfs_panic(btrfs_sb(inode->i_sb), err,
	"locking error: extent tree was modified by another thread while locked");
}