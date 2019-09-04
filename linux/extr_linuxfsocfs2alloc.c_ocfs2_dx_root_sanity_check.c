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
struct ocfs2_extent_tree {struct ocfs2_dx_root_block* et_object; } ;
struct ocfs2_dx_root_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DX_ROOT (struct ocfs2_dx_root_block*) ; 

__attribute__((used)) static int ocfs2_dx_root_sanity_check(struct ocfs2_extent_tree *et)
{
	struct ocfs2_dx_root_block *dx_root = et->et_object;

	BUG_ON(!OCFS2_IS_VALID_DX_ROOT(dx_root));

	return 0;
}