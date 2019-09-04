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
struct ocfs2_extent_tree {int /*<<< orphan*/ * et_ops; struct ocfs2_dinode* et_object; } ;
struct ocfs2_dinode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  ocfs2_dinode_et_ops ; 

__attribute__((used)) static int ocfs2_dinode_sanity_check(struct ocfs2_extent_tree *et)
{
	struct ocfs2_dinode *di = et->et_object;

	BUG_ON(et->et_ops != &ocfs2_dinode_et_ops);
	BUG_ON(!OCFS2_IS_VALID_DINODE(di));

	return 0;
}