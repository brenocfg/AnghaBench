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
struct ocfs2_extent_tree {int /*<<< orphan*/  et_max_leaf_clusters; int /*<<< orphan*/  et_ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_MAX_XATTR_TREE_LEAF_SIZE ; 
 int /*<<< orphan*/  ocfs2_clusters_for_bytes (struct super_block*,int /*<<< orphan*/ ) ; 
 struct super_block* ocfs2_metadata_cache_get_super (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_xattr_tree_fill_max_leaf_clusters(struct ocfs2_extent_tree *et)
{
	struct super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	et->et_max_leaf_clusters =
		ocfs2_clusters_for_bytes(sb, OCFS2_MAX_XATTR_TREE_LEAF_SIZE);
}