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
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {TYPE_1__* b_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_CRIT ; 
 int /*<<< orphan*/  dump_stack () ; 
 int nilfs_btree_node_get_level (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_btree_bad_node(const struct nilfs_bmap *btree,
				struct nilfs_btree_node *node, int level)
{
	if (unlikely(nilfs_btree_node_get_level(node) != level)) {
		dump_stack();
		nilfs_msg(btree->b_inode->i_sb, KERN_CRIT,
			  "btree level mismatch (ino=%lu): %d != %d",
			  btree->b_inode->i_ino,
			  nilfs_btree_node_get_level(node), level);
		return 1;
	}
	return 0;
}