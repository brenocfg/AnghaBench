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
struct aa_label {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 struct aa_label* aa_get_newest_label (struct aa_label*) ; 
 struct aa_label* aa_label_alloc (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  label_free_or_put_new (struct aa_label*,struct aa_label*) ; 
 struct aa_label* label_merge_insert (struct aa_label*,struct aa_label*,struct aa_label*) ; 

struct aa_label *aa_label_merge(struct aa_label *a, struct aa_label *b,
				gfp_t gfp)
{
	struct aa_label *label = NULL;

	AA_BUG(!a);
	AA_BUG(!b);

	if (a == b)
		return aa_get_newest_label(a);

	/* TODO: enable when read side is lockless
	 * check if label exists before taking locks
	if (!label_is_stale(a) && !label_is_stale(b))
		label = aa_label_find_merge(a, b);
	*/

	if (!label) {
		struct aa_label *new;

		a = aa_get_newest_label(a);
		b = aa_get_newest_label(b);

		/* could use label_merge_len(a, b), but requires double
		 * comparison for small savings
		 */
		new = aa_label_alloc(a->size + b->size, NULL, gfp);
		if (!new)
			goto out;

		label = label_merge_insert(new, a, b);
		label_free_or_put_new(label, new);
out:
		aa_put_label(a);
		aa_put_label(b);
	}

	return label;
}