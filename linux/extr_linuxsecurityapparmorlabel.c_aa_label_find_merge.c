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
struct aa_labelset {int /*<<< orphan*/  lock; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 struct aa_label* __label_find_merge (struct aa_labelset*,struct aa_label*,struct aa_label*) ; 
 struct aa_label* aa_get_newest_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 scalar_t__ label_is_stale (struct aa_label*) ; 
 struct aa_labelset* labelset_of_merge (struct aa_label*,struct aa_label*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct aa_label *aa_label_find_merge(struct aa_label *a, struct aa_label *b)
{
	struct aa_labelset *ls;
	struct aa_label *label, *ar = NULL, *br = NULL;
	unsigned long flags;

	AA_BUG(!a);
	AA_BUG(!b);

	if (label_is_stale(a))
		a = ar = aa_get_newest_label(a);
	if (label_is_stale(b))
		b = br = aa_get_newest_label(b);
	ls = labelset_of_merge(a, b);
	read_lock_irqsave(&ls->lock, flags);
	label = __label_find_merge(ls, a, b);
	read_unlock_irqrestore(&ls->lock, flags);
	aa_put_label(ar);
	aa_put_label(br);

	return label;
}