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
struct ulist_node {int /*<<< orphan*/  val; } ;
struct ulist_iterator {int dummy; } ;
struct ulist {scalar_t__ nnodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULIST_ITER_INIT (struct ulist_iterator*) ; 
 int is_fstree (int /*<<< orphan*/ ) ; 
 struct ulist_node* ulist_next (struct ulist*,struct ulist_iterator*) ; 

__attribute__((used)) static int maybe_fs_roots(struct ulist *roots)
{
	struct ulist_node *unode;
	struct ulist_iterator uiter;

	/* Empty one, still possible for fs roots */
	if (!roots || roots->nnodes == 0)
		return 1;

	ULIST_ITER_INIT(&uiter);
	unode = ulist_next(roots, &uiter);
	if (!unode)
		return 1;

	/*
	 * If it contains fs tree roots, then it must belong to fs/subvol
	 * trees.
	 * If it contains a non-fs tree, it won't be shared with fs/subvol trees.
	 */
	return is_fstree(unode->val);
}