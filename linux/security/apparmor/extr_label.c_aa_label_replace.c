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
struct aa_label {scalar_t__ proxy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aa_proxy_redirect (struct aa_label*,struct aa_label*) ; 
 struct aa_label* __label_insert (struct aa_labelset*,struct aa_label*,int) ; 
 int __label_remove (struct aa_label*,struct aa_label*) ; 
 int __label_replace (struct aa_label*,struct aa_label*) ; 
 int /*<<< orphan*/  __proxy_share (struct aa_label*,struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 scalar_t__ labels_ns (struct aa_label*) ; 
 struct aa_labelset* labels_set (struct aa_label*) ; 
 scalar_t__ name_is_shared (struct aa_label*,struct aa_label*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool aa_label_replace(struct aa_label *old, struct aa_label *new)
{
	unsigned long flags;
	bool res;

	if (name_is_shared(old, new) && labels_ns(old) == labels_ns(new)) {
		write_lock_irqsave(&labels_set(old)->lock, flags);
		if (old->proxy != new->proxy)
			__proxy_share(old, new);
		else
			__aa_proxy_redirect(old, new);
		res = __label_replace(old, new);
		write_unlock_irqrestore(&labels_set(old)->lock, flags);
	} else {
		struct aa_label *l;
		struct aa_labelset *ls = labels_set(old);

		write_lock_irqsave(&ls->lock, flags);
		res = __label_remove(old, new);
		if (labels_ns(old) != labels_ns(new)) {
			write_unlock_irqrestore(&ls->lock, flags);
			ls = labels_set(new);
			write_lock_irqsave(&ls->lock, flags);
		}
		l = __label_insert(ls, new, true);
		res = (l == new);
		write_unlock_irqrestore(&ls->lock, flags);
		aa_put_label(l);
	}

	return res;
}