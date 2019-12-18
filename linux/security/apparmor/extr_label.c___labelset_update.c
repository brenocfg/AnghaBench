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
struct aa_ns {int /*<<< orphan*/  labels; int /*<<< orphan*/  lock; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 struct aa_label* __label_update (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 struct aa_label* labelset_next_stale (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __labelset_update(struct aa_ns *ns)
{
	struct aa_label *label;

	AA_BUG(!ns);
	AA_BUG(!mutex_is_locked(&ns->lock));

	do {
		label = labelset_next_stale(&ns->labels);
		if (label) {
			struct aa_label *l = __label_update(label);

			aa_put_label(l);
			aa_put_label(label);
		}
	} while (label);
}