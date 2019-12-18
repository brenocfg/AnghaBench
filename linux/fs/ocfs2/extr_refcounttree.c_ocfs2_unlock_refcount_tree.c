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
struct ocfs2_super {int dummy; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_refcount_tree_put (struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  ocfs2_refcount_unlock (struct ocfs2_refcount_tree*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ocfs2_unlock_refcount_tree(struct ocfs2_super *osb,
				struct ocfs2_refcount_tree *tree, int rw)
{
	if (rw)
		up_write(&tree->rf_sem);
	else
		up_read(&tree->rf_sem);

	ocfs2_refcount_unlock(tree, rw);
	ocfs2_refcount_tree_put(tree);
}