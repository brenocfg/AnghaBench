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
 int /*<<< orphan*/  __aa_proxy_redirect (struct aa_label*,struct aa_label*) ; 
 int /*<<< orphan*/  __label_make_stale (struct aa_label*) ; 
 int /*<<< orphan*/  label_is_stale (struct aa_label*) ; 
 struct aa_labelset* labels_set (struct aa_label*) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __label_remove(struct aa_label *label, struct aa_label *new)
{
	struct aa_labelset *ls = labels_set(label);

	AA_BUG(!ls);
	AA_BUG(!label);
	lockdep_assert_held_write(&ls->lock);

	if (new)
		__aa_proxy_redirect(label, new);

	if (!label_is_stale(label))
		__label_make_stale(label);

	if (label->flags & FLAG_IN_TREE) {
		rb_erase(&label->node, &ls->root);
		label->flags &= ~FLAG_IN_TREE;
		return true;
	}

	return false;
}