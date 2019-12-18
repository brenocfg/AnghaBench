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
 int __label_remove (struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  labels_ns (struct aa_label*) ; 
 struct aa_labelset* labels_set (struct aa_label*) ; 
 int /*<<< orphan*/  ns_unconfined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool aa_label_remove(struct aa_label *label)
{
	struct aa_labelset *ls = labels_set(label);
	unsigned long flags;
	bool res;

	AA_BUG(!ls);

	write_lock_irqsave(&ls->lock, flags);
	res = __label_remove(label, ns_unconfined(labels_ns(label)));
	write_unlock_irqrestore(&ls->lock, flags);

	return res;
}