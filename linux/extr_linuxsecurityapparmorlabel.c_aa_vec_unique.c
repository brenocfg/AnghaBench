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
struct aa_profile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int VEC_FLAG_TERMINATE ; 
 int /*<<< orphan*/  aa_put_profile (struct aa_profile*) ; 
 int profile_cmp (struct aa_profile*,struct aa_profile*) ; 
 int /*<<< orphan*/  sort (struct aa_profile**,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_cmp ; 
 int unique (struct aa_profile**,int) ; 

int aa_vec_unique(struct aa_profile **vec, int n, int flags)
{
	int i, dups = 0;

	AA_BUG(n < 1);
	AA_BUG(!vec);

	/* vecs are usually small and inorder, have a fallback for larger */
	if (n > 8) {
		sort(vec, n, sizeof(struct aa_profile *), sort_cmp, NULL);
		dups = unique(vec, n);
		goto out;
	}

	/* insertion sort + unique in one */
	for (i = 1; i < n; i++) {
		struct aa_profile *tmp = vec[i];
		int pos, j;

		for (pos = i - 1 - dups; pos >= 0; pos--) {
			int res = profile_cmp(vec[pos], tmp);

			if (res == 0) {
				/* drop duplicate entry */
				aa_put_profile(tmp);
				dups++;
				goto continue_outer;
			} else if (res < 0)
				break;
		}
		/* pos is at entry < tmp, or index -1. Set to insert pos */
		pos++;

		for (j = i - dups; j > pos; j--)
			vec[j] = vec[j - 1];
		vec[pos] = tmp;
continue_outer:
		;
	}

	AA_BUG(dups < 0);

out:
	if (flags & VEC_FLAG_TERMINATE)
		vec[n - dups] = NULL;

	return dups;
}