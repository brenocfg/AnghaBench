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
struct ocfs2_xattr_value_buf {int /*<<< orphan*/  vb_access; int /*<<< orphan*/  vb_bh; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ocfs2_init_extent_tree (struct ocfs2_extent_tree*,struct ocfs2_caching_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_xattr_value_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_xattr_value_et_ops ; 

void ocfs2_init_xattr_value_extent_tree(struct ocfs2_extent_tree *et,
					struct ocfs2_caching_info *ci,
					struct ocfs2_xattr_value_buf *vb)
{
	__ocfs2_init_extent_tree(et, ci, vb->vb_bh, vb->vb_access, vb,
				 &ocfs2_xattr_value_et_ops);
}