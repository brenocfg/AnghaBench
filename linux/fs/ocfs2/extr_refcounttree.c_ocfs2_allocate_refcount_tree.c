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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_getcnt; int /*<<< orphan*/  rf_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct ocfs2_refcount_tree* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_init_refcount_tree_ci (struct ocfs2_refcount_tree*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocfs2_refcount_tree*
ocfs2_allocate_refcount_tree(struct ocfs2_super *osb, u64 rf_blkno)
{
	struct ocfs2_refcount_tree *new;

	new = kzalloc(sizeof(struct ocfs2_refcount_tree), GFP_NOFS);
	if (!new)
		return NULL;

	new->rf_blkno = rf_blkno;
	kref_init(&new->rf_getcnt);
	ocfs2_init_refcount_tree_ci(new, osb->sb);

	return new;
}