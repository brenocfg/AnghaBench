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
struct aa_profile {int dummy; } ;
struct aa_label {int size; int /*<<< orphan*/ * vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 struct aa_profile* aa_label_next_in_merge (struct label_it*,struct aa_label*,struct aa_label*) ; 
 int profile_cmp (struct aa_profile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int label_merge_cmp(struct aa_label *a, struct aa_label *b,
			   struct aa_label *z)
{
	struct aa_profile *p = NULL;
	struct label_it i = { };
	int k;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!z);

	for (k = 0;
	     k < z->size && (p = aa_label_next_in_merge(&i, a, b));
	     k++) {
		int res = profile_cmp(p, z->vec[k]);

		if (res != 0)
			return res;
	}

	if (p)
		return 1;
	else if (k < z->size)
		return -1;
	return 0;
}