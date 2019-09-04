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
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_lockres; int /*<<< orphan*/  rf_sb; int /*<<< orphan*/  rf_ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_simple_drop_lockres (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_free_refcount_tree(struct ocfs2_refcount_tree *tree)
{
	ocfs2_metadata_cache_exit(&tree->rf_ci);
	ocfs2_simple_drop_lockres(OCFS2_SB(tree->rf_sb), &tree->rf_lockres);
	ocfs2_lock_res_free(&tree->rf_lockres);
	kfree(tree);
}