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
 scalar_t__ profile_is_stale (struct aa_profile*) ; 

__attribute__((used)) static bool vec_is_stale(struct aa_profile **vec, int n)
{
	int i;

	AA_BUG(!vec);

	for (i = 0; i < n; i++) {
		if (profile_is_stale(vec[i]))
			return true;
	}

	return false;
}