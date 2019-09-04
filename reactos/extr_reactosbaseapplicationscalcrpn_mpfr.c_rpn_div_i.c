#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_10__ {int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_8__ calc ; 
 scalar_t__ mpfr_sgn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_tdiv_q ; 
 int /*<<< orphan*/  rpn_exec_int (TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpn_div_i(calc_number_t *r, calc_number_t *a, calc_number_t *b)
{
    if (mpfr_sgn(b->mf) == 0)
        calc.is_nan = TRUE;
    else
        rpn_exec_int(r, a, b, mpz_tdiv_q);
}