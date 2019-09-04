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
struct gf_poly {int deg; scalar_t__* c; } ;
struct bch_control {int dummy; } ;

/* Variables and functions */
 int GF_N (struct bch_control*) ; 
 int a_log (struct bch_control*,scalar_t__) ; 
 int mod_s (struct bch_control*,int) ; 

__attribute__((used)) static void gf_poly_logrep(struct bch_control *bch,
			   const struct gf_poly *a, int *rep)
{
	int i, d = a->deg, l = GF_N(bch)-a_log(bch, a->c[a->deg]);

	/* represent 0 values with -1; warning, rep[d] is not set to 1 */
	for (i = 0; i < d; i++)
		rep[i] = a->c[i] ? mod_s(bch, a_log(bch, a->c[i])+l) : -1;
}