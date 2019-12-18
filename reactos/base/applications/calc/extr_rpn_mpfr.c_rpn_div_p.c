#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_7__ {int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ calc ; 
 int /*<<< orphan*/  mpfr_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_mul_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mpfr_sgn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpn_div_p(calc_number_t *r, calc_number_t *a, calc_number_t *b)
{
    if (mpfr_sgn(b->mf) == 0)
        calc.is_nan = TRUE;
    else {
        mpfr_mul_ui(r->mf, a->mf, 100, MPFR_DEFAULT_RND);
        mpfr_div(r->mf, r->mf, b->mf, MPFR_DEFAULT_RND);
    }
}