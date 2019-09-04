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
struct TYPE_5__ {int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ calc ; 
 scalar_t__ mpfr_sgn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_ui_div (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rpn_reci(calc_number_t *c)
{
    if (mpfr_sgn(c->mf) == 0)
        calc.is_nan = TRUE;
    else
        mpfr_ui_div(c->mf, 1, c->mf, MPFR_DEFAULT_RND);
}