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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int Min (int,int) ; 

__attribute__((used)) static int
n_choose_k(int n, int k)
{
	int			d,
				r;

	Assert((k > 0) && (n >= k));

	/* use symmetry of the binomial coefficients */
	k = Min(k, n - k);

	r = 1;
	for (d = 1; d <= k; ++d)
	{
		r *= n--;
		r /= d;
	}

	return r;
}