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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_xattr_tree_root {int /*<<< orphan*/  xt_last_eb_blk; } ;
struct TYPE_2__ {struct ocfs2_xattr_tree_root xb_root; } ;
struct ocfs2_xattr_block {TYPE_1__ xb_attrs; } ;
struct ocfs2_extent_tree {struct ocfs2_xattr_block* et_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ocfs2_xattr_tree_get_last_eb_blk(struct ocfs2_extent_tree *et)
{
	struct ocfs2_xattr_block *xb = et->et_object;
	struct ocfs2_xattr_tree_root *xt = &xb->xb_attrs.xb_root;

	return le64_to_cpu(xt->xt_last_eb_blk);
}