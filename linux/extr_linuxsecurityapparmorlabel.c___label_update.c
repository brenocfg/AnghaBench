#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct aa_labelset {int /*<<< orphan*/  lock; } ;
struct aa_label {int size; TYPE_3__** vec; int /*<<< orphan*/  proxy; } ;
struct TYPE_10__ {TYPE_1__* proxy; } ;
struct TYPE_9__ {TYPE_6__ label; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VEC_FLAG_TERMINATE ; 
 struct aa_label* __label_insert (struct aa_labelset*,struct aa_label*,int) ; 
 int /*<<< orphan*/  __label_remove (struct aa_label*,struct aa_label*) ; 
 struct aa_label* aa_get_label (TYPE_6__*) ; 
 TYPE_3__* aa_get_newest_profile (TYPE_3__*) ; 
 struct aa_label* aa_label_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aa_label* aa_label_insert (struct aa_labelset*,struct aa_label*) ; 
 scalar_t__ aa_vec_unique (TYPE_3__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_free_or_put_new (struct aa_label*,struct aa_label*) ; 
 TYPE_2__* labels_ns (struct aa_label*) ; 
 struct aa_labelset* labels_set (struct aa_label*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct aa_label *__label_update(struct aa_label *label)
{
	struct aa_label *new, *tmp;
	struct aa_labelset *ls;
	unsigned long flags;
	int i, invcount = 0;

	AA_BUG(!label);
	AA_BUG(!mutex_is_locked(&labels_ns(label)->lock));

	new = aa_label_alloc(label->size, label->proxy, GFP_KERNEL);
	if (!new)
		return NULL;

	/*
	 * while holding the ns_lock will stop profile replacement, removal,
	 * and label updates, label merging and removal can be occurring
	 */
	ls = labels_set(label);
	write_lock_irqsave(&ls->lock, flags);
	for (i = 0; i < label->size; i++) {
		AA_BUG(!label->vec[i]);
		new->vec[i] = aa_get_newest_profile(label->vec[i]);
		AA_BUG(!new->vec[i]);
		AA_BUG(!new->vec[i]->label.proxy);
		AA_BUG(!new->vec[i]->label.proxy->label);
		if (new->vec[i]->label.proxy != label->vec[i]->label.proxy)
			invcount++;
	}

	/* updated stale label by being removed/renamed from labelset */
	if (invcount) {
		new->size -= aa_vec_unique(&new->vec[0], new->size,
					   VEC_FLAG_TERMINATE);
		/* TODO: deal with reference labels */
		if (new->size == 1) {
			tmp = aa_get_label(&new->vec[0]->label);
			AA_BUG(tmp == label);
			goto remove;
		}
		if (labels_set(label) != labels_set(new)) {
			write_unlock_irqrestore(&ls->lock, flags);
			tmp = aa_label_insert(labels_set(new), new);
			write_lock_irqsave(&ls->lock, flags);
			goto remove;
		}
	} else
		AA_BUG(labels_ns(label) != labels_ns(new));

	tmp = __label_insert(labels_set(label), new, true);
remove:
	/* ensure label is removed, and redirected correctly */
	__label_remove(label, tmp);
	write_unlock_irqrestore(&ls->lock, flags);
	label_free_or_put_new(tmp, new);

	return tmp;
}