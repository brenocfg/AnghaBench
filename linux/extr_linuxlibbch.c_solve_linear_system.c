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
struct bch_control {int dummy; } ;

/* Variables and functions */
 int BCH_MAX_M ; 
 int GF_M (struct bch_control*) ; 
 int const parity (unsigned int) ; 

__attribute__((used)) static int solve_linear_system(struct bch_control *bch, unsigned int *rows,
			       unsigned int *sol, int nsol)
{
	const int m = GF_M(bch);
	unsigned int tmp, mask;
	int rem, c, r, p, k, param[BCH_MAX_M];

	k = 0;
	mask = 1 << m;

	/* Gaussian elimination */
	for (c = 0; c < m; c++) {
		rem = 0;
		p = c-k;
		/* find suitable row for elimination */
		for (r = p; r < m; r++) {
			if (rows[r] & mask) {
				if (r != p) {
					tmp = rows[r];
					rows[r] = rows[p];
					rows[p] = tmp;
				}
				rem = r+1;
				break;
			}
		}
		if (rem) {
			/* perform elimination on remaining rows */
			tmp = rows[p];
			for (r = rem; r < m; r++) {
				if (rows[r] & mask)
					rows[r] ^= tmp;
			}
		} else {
			/* elimination not needed, store defective row index */
			param[k++] = c;
		}
		mask >>= 1;
	}
	/* rewrite system, inserting fake parameter rows */
	if (k > 0) {
		p = k;
		for (r = m-1; r >= 0; r--) {
			if ((r > m-1-k) && rows[r])
				/* system has no solution */
				return 0;

			rows[r] = (p && (r == param[p-1])) ?
				p--, 1u << (m-r) : rows[r-p];
		}
	}

	if (nsol != (1 << k))
		/* unexpected number of solutions */
		return 0;

	for (p = 0; p < nsol; p++) {
		/* set parameters for p-th solution */
		for (c = 0; c < k; c++)
			rows[param[c]] = (rows[param[c]] & ~1)|((p >> c) & 1);

		/* compute unique solution */
		tmp = 0;
		for (r = m-1; r >= 0; r--) {
			mask = rows[r] & (tmp|1);
			tmp |= parity(mask) << (m-r);
		}
		sol[p] = tmp >> 1;
	}
	return nsol;
}