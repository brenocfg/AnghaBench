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
struct gf_poly {size_t deg; scalar_t__* c; } ;
struct bch_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf_poly_mod (struct bch_control*,struct gf_poly*,struct gf_poly const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void gf_poly_div(struct bch_control *bch, struct gf_poly *a,
			const struct gf_poly *b, struct gf_poly *q)
{
	if (a->deg >= b->deg) {
		q->deg = a->deg-b->deg;
		/* compute a mod b (modifies a) */
		gf_poly_mod(bch, a, b, NULL);
		/* quotient is stored in upper part of polynomial a */
		memcpy(q->c, &a->c[b->deg], (1+q->deg)*sizeof(unsigned int));
	} else {
		q->deg = 0;
		q->c[0] = 0;
	}
}