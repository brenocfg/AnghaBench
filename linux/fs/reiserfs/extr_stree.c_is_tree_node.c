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
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int B_LEVEL (struct buffer_head*) ; 
 int DISK_LEAF_NODE_LEVEL ; 
 int is_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int is_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ *,char*,char*,int,int) ; 

__attribute__((used)) static int is_tree_node(struct buffer_head *bh, int level)
{
	if (B_LEVEL(bh) != level) {
		reiserfs_warning(NULL, "reiserfs-5090", "node level %d does "
				 "not match to the expected one %d",
				 B_LEVEL(bh), level);
		return 0;
	}
	if (level == DISK_LEAF_NODE_LEVEL)
		return is_leaf(bh->b_data, bh->b_size, bh);

	return is_internal(bh->b_data, bh->b_size, bh);
}