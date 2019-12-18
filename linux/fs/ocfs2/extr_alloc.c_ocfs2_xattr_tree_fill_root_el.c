#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xt_list; } ;
struct TYPE_4__ {TYPE_1__ xb_root; } ;
struct ocfs2_xattr_block {TYPE_2__ xb_attrs; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/ * et_root_el; struct ocfs2_xattr_block* et_object; } ;

/* Variables and functions */

__attribute__((used)) static void ocfs2_xattr_tree_fill_root_el(struct ocfs2_extent_tree *et)
{
	struct ocfs2_xattr_block *xb = et->et_object;

	et->et_root_el = &xb->xb_attrs.xb_root.xt_list;
}