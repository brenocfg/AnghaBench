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
struct nilfs_btree_path {scalar_t__ bp_index; int /*<<< orphan*/  bp_bh; } ;
struct nilfs_bmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 int /*<<< orphan*/  nilfs_btree_get_root (struct nilfs_bmap*) ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_key (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_btree_promote_key(struct nilfs_bmap *btree,
				    struct nilfs_btree_path *path,
				    int level, __u64 key)
{
	if (level < nilfs_btree_height(btree) - 1) {
		do {
			nilfs_btree_node_set_key(
				nilfs_btree_get_nonroot_node(path, level),
				path[level].bp_index, key);
			if (!buffer_dirty(path[level].bp_bh))
				mark_buffer_dirty(path[level].bp_bh);
		} while ((path[level].bp_index == 0) &&
			 (++level < nilfs_btree_height(btree) - 1));
	}

	/* root */
	if (level == nilfs_btree_height(btree) - 1) {
		nilfs_btree_node_set_key(nilfs_btree_get_root(btree),
					 path[level].bp_index, key);
	}
}