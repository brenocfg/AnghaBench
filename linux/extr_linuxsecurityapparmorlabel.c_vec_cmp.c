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
 int profile_cmp (struct aa_profile*,struct aa_profile*) ; 

__attribute__((used)) static int vec_cmp(struct aa_profile **a, int an, struct aa_profile **b, int bn)
{
	int i;

	AA_BUG(!a);
	AA_BUG(!*a);
	AA_BUG(!b);
	AA_BUG(!*b);
	AA_BUG(an <= 0);
	AA_BUG(bn <= 0);

	for (i = 0; i < an && i < bn; i++) {
		int res = profile_cmp(a[i], b[i]);

		if (res != 0)
			return res;
	}

	return an - bn;
}