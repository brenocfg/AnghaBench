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
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ocfs2_init_extent_tree (struct ocfs2_extent_tree*,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_journal_access_xb ; 
 int /*<<< orphan*/  ocfs2_xattr_tree_et_ops ; 

void ocfs2_init_xattr_tree_extent_tree(struct ocfs2_extent_tree *et,
				       struct ocfs2_caching_info *ci,
				       struct buffer_head *bh)
{
	__ocfs2_init_extent_tree(et, ci, bh, ocfs2_journal_access_xb,
				 NULL, &ocfs2_xattr_tree_et_ops);
}