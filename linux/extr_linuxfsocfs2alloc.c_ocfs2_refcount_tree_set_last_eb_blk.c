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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_refcount_block {int /*<<< orphan*/  rf_last_eb_blk; } ;
struct ocfs2_extent_tree {struct ocfs2_refcount_block* et_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_refcount_tree_set_last_eb_blk(struct ocfs2_extent_tree *et,
						u64 blkno)
{
	struct ocfs2_refcount_block *rb = et->et_object;

	rb->rf_last_eb_blk = cpu_to_le64(blkno);
}