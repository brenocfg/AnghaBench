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
typedef  unsigned int uint32_t ;
struct bch_control {int ecc_bits; } ;

/* Variables and functions */
 int GF_T (struct bch_control*) ; 
 unsigned int a_pow (struct bch_control*,int) ; 
 int deg (unsigned int) ; 
 unsigned int gf_sqr (struct bch_control*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void compute_syndromes(struct bch_control *bch, uint32_t *ecc,
			      unsigned int *syn)
{
	int i, j, s;
	unsigned int m;
	uint32_t poly;
	const int t = GF_T(bch);

	s = bch->ecc_bits;

	/* make sure extra bits in last ecc word are cleared */
	m = ((unsigned int)s) & 31;
	if (m)
		ecc[s/32] &= ~((1u << (32-m))-1);
	memset(syn, 0, 2*t*sizeof(*syn));

	/* compute v(a^j) for j=1 .. 2t-1 */
	do {
		poly = *ecc++;
		s -= 32;
		while (poly) {
			i = deg(poly);
			for (j = 0; j < 2*t; j += 2)
				syn[j] ^= a_pow(bch, (j+1)*(i+s));

			poly ^= (1 << i);
		}
	} while (s > 0);

	/* v(a^(2j)) = v(a^j)^2 */
	for (j = 0; j < t; j++)
		syn[2*j+1] = gf_sqr(bch, syn[j]);
}