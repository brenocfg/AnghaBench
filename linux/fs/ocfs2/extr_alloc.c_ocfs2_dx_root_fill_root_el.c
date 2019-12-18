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
struct ocfs2_extent_tree {int /*<<< orphan*/ * et_root_el; struct ocfs2_dx_root_block* et_object; } ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_list; } ;

/* Variables and functions */

__attribute__((used)) static void ocfs2_dx_root_fill_root_el(struct ocfs2_extent_tree *et)
{
	struct ocfs2_dx_root_block *dx_root = et->et_object;

	et->et_root_el = &dx_root->dr_list;
}