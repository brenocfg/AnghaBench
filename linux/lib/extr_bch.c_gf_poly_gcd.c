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
struct gf_poly {scalar_t__ deg; } ;
struct bch_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gf_poly_mod (struct bch_control*,struct gf_poly*,struct gf_poly*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf_poly_str (struct gf_poly*) ; 

__attribute__((used)) static struct gf_poly *gf_poly_gcd(struct bch_control *bch, struct gf_poly *a,
				   struct gf_poly *b)
{
	struct gf_poly *tmp;

	dbg("gcd(%s,%s)=", gf_poly_str(a), gf_poly_str(b));

	if (a->deg < b->deg) {
		tmp = b;
		b = a;
		a = tmp;
	}

	while (b->deg > 0) {
		gf_poly_mod(bch, a, b, NULL);
		tmp = b;
		b = a;
		a = tmp;
	}

	dbg("%s\n", gf_poly_str(a));

	return a;
}