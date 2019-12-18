#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_5__ {void* is_nan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 void* TRUE ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  mpfr_fac_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mpfr_fits_ulong_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_get_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_number_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mpfr_sgn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rpn_fact(calc_number_t *c)
{
    if (mpfr_sgn(c->mf) < 0) {
        calc.is_nan = TRUE;
        return;
    }

    mpfr_trunc(c->mf, c->mf);
    if (mpfr_fits_ulong_p(c->mf, MPFR_DEFAULT_RND) == 0)
        calc.is_nan = TRUE;
    else {
        mpfr_fac_ui(c->mf, mpfr_get_ui(c->mf, MPFR_DEFAULT_RND), MPFR_DEFAULT_RND);
        if (!mpfr_number_p(c->mf)) calc.is_nan = TRUE;
    }
}