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
struct aa_profile {int /*<<< orphan*/  label; } ;
struct aa_labelset {int /*<<< orphan*/  lock; } ;
struct aa_label {int /*<<< orphan*/ * vec; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 struct aa_label* __label_insert (struct aa_labelset*,struct aa_label*,int) ; 
 struct aa_label* aa_get_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aa_get_profile (struct aa_profile*) ; 
 struct aa_label* aa_label_alloc (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_free_or_put_new (struct aa_label*,struct aa_label*) ; 
 struct aa_labelset* labels_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct aa_label *vec_create_and_insert_label(struct aa_profile **vec,
						    int len, gfp_t gfp)
{
	struct aa_label *label = NULL;
	struct aa_labelset *ls;
	unsigned long flags;
	struct aa_label *new;
	int i;

	AA_BUG(!vec);

	if (len == 1)
		return aa_get_label(&vec[0]->label);

	ls = labels_set(&vec[len - 1]->label);

	/* TODO: enable when read side is lockless
	 * check if label exists before taking locks
	 */
	new = aa_label_alloc(len, NULL, gfp);
	if (!new)
		return NULL;

	for (i = 0; i < len; i++)
		new->vec[i] = aa_get_profile(vec[i]);

	write_lock_irqsave(&ls->lock, flags);
	label = __label_insert(ls, new, false);
	write_unlock_irqrestore(&ls->lock, flags);
	label_free_or_put_new(label, new);

	return label;
}