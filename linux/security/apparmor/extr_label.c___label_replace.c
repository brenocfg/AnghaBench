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
struct aa_labelset {int /*<<< orphan*/  root; int /*<<< orphan*/  lock; } ;
struct aa_label {int flags; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int FLAG_IN_TREE ; 
 int /*<<< orphan*/  __label_make_stale (struct aa_label*) ; 
 int /*<<< orphan*/  label_is_stale (struct aa_label*) ; 
 struct aa_labelset* labels_set (struct aa_label*) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_replace_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __label_replace(struct aa_label *old, struct aa_label *new)
{
	struct aa_labelset *ls = labels_set(old);

	AA_BUG(!ls);
	AA_BUG(!old);
	AA_BUG(!new);
	lockdep_assert_held_write(&ls->lock);
	AA_BUG(new->flags & FLAG_IN_TREE);

	if (!label_is_stale(old))
		__label_make_stale(old);

	if (old->flags & FLAG_IN_TREE) {
		rb_replace_node(&old->node, &new->node, &ls->root);
		old->flags &= ~FLAG_IN_TREE;
		new->flags |= FLAG_IN_TREE;
		return true;
	}

	return false;
}