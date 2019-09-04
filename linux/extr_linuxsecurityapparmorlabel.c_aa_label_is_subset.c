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
struct label_it {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/ * __aa_label_next_not_in_set (struct label_it*,struct aa_label*,struct aa_label*) ; 

bool aa_label_is_subset(struct aa_label *set, struct aa_label *sub)
{
	struct label_it i = { };

	AA_BUG(!set);
	AA_BUG(!sub);

	if (sub == set)
		return true;

	return __aa_label_next_not_in_set(&i, set, sub) == NULL;
}