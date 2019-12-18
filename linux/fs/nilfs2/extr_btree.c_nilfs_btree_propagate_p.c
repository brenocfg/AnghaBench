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
struct nilfs_btree_path {int /*<<< orphan*/  bp_bh; } ;
struct nilfs_bmap {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 

__attribute__((used)) static int nilfs_btree_propagate_p(struct nilfs_bmap *btree,
				   struct nilfs_btree_path *path,
				   int level,
				   struct buffer_head *bh)
{
	while ((++level < nilfs_btree_height(btree) - 1) &&
	       !buffer_dirty(path[level].bp_bh))
		mark_buffer_dirty(path[level].bp_bh);

	return 0;
}