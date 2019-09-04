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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct buffer_head** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int ocfs2_clusters_to_blocks (struct super_block*,int) ; 

__attribute__((used)) static struct buffer_head **ocfs2_dx_dir_kmalloc_leaves(struct super_block *sb,
							int *ret_num_leaves)
{
	int num_dx_leaves = ocfs2_clusters_to_blocks(sb, 1);
	struct buffer_head **dx_leaves;

	dx_leaves = kcalloc(num_dx_leaves, sizeof(struct buffer_head *),
			    GFP_NOFS);
	if (dx_leaves && ret_num_leaves)
		*ret_num_leaves = num_dx_leaves;

	return dx_leaves;
}