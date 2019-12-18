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
 struct aa_label* __label_find (struct aa_label*) ; 
 struct aa_label* __label_insert (struct aa_labelset*,struct aa_label*,int) ; 
 int /*<<< orphan*/  label_is_stale (struct aa_label*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct aa_label *aa_label_insert(struct aa_labelset *ls, struct aa_label *label)
{
	struct aa_label *l;
	unsigned long flags;

	AA_BUG(!ls);
	AA_BUG(!label);

	/* check if label exists before taking lock */
	if (!label_is_stale(label)) {
		read_lock_irqsave(&ls->lock, flags);
		l = __label_find(label);
		read_unlock_irqrestore(&ls->lock, flags);
		if (l)
			return l;
	}

	write_lock_irqsave(&ls->lock, flags);
	l = __label_insert(ls, label, false);
	write_unlock_irqrestore(&ls->lock, flags);

	return l;
}