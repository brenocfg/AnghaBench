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
struct nilfs_btree_node {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_CRIT ; 
 int NILFS_BTREE_LEVEL_MAX ; 
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int nilfs_btree_node_get_flags (struct nilfs_btree_node const*) ; 
 int nilfs_btree_node_get_level (struct nilfs_btree_node const*) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node const*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_btree_root_broken(const struct nilfs_btree_node *node,
				   struct inode *inode)
{
	int level, flags, nchildren;
	int ret = 0;

	level = nilfs_btree_node_get_level(node);
	flags = nilfs_btree_node_get_flags(node);
	nchildren = nilfs_btree_node_get_nchildren(node);

	if (unlikely(level < NILFS_BTREE_LEVEL_NODE_MIN ||
		     level >= NILFS_BTREE_LEVEL_MAX ||
		     nchildren < 0 ||
		     nchildren > NILFS_BTREE_ROOT_NCHILDREN_MAX)) {
		nilfs_msg(inode->i_sb, KERN_CRIT,
			  "bad btree root (ino=%lu): level = %d, flags = 0x%x, nchildren = %d",
			  inode->i_ino, level, flags, nchildren);
		ret = 1;
	}
	return ret;
}