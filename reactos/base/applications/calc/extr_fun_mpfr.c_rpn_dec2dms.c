#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpfr_t ;
struct TYPE_3__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int /*<<< orphan*/  mpfr_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_ceil (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_div_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_frac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_mul_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rpn_dec2dms(calc_number_t *c)
{
    mpfr_t d, m, s;

    mpfr_init(d);
    mpfr_init(m);
    mpfr_init(s);

    mpfr_trunc(d, c->mf);
    mpfr_frac(m, c->mf, MPFR_DEFAULT_RND);
    mpfr_mul_ui(m, m, 60, MPFR_DEFAULT_RND);

    mpfr_frac(s, m, MPFR_DEFAULT_RND);
    mpfr_trunc(m, m);
    mpfr_mul_ui(s, s, 60, MPFR_DEFAULT_RND);
    mpfr_ceil(s, s);

    mpfr_div_ui(m, m, 100, MPFR_DEFAULT_RND);
    mpfr_div_ui(s, s, 10000, MPFR_DEFAULT_RND);
    mpfr_add(c->mf, d, m, MPFR_DEFAULT_RND);
    mpfr_add(c->mf, c->mf, s, MPFR_DEFAULT_RND);

    mpfr_clear(d);
    mpfr_clear(m);
    mpfr_clear(s);
}