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
typedef  int /*<<< orphan*/  mpfr_t ;
struct TYPE_4__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_5__ {int degr; } ;

/* Variables and functions */
#define  IDC_RADIO_DEG 130 
#define  IDC_RADIO_GRAD 129 
#define  IDC_RADIO_RAD 128 
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  mpfr_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_const_pi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_set_ui (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void validate_rad2angle(calc_number_t *r)
{
    mpfr_t mult, divs;

    mpfr_init(mult);
    mpfr_init(divs);
    switch (calc.degr) {
    case IDC_RADIO_DEG:
        mpfr_set_ui(mult, 180, MPFR_DEFAULT_RND);
        mpfr_const_pi(divs, MPFR_DEFAULT_RND);
        break;
    case IDC_RADIO_RAD:
        mpfr_set_ui(mult, 1, MPFR_DEFAULT_RND);
        mpfr_set_ui(divs, 1, MPFR_DEFAULT_RND);
        break;
    case IDC_RADIO_GRAD:
        mpfr_set_ui(mult, 200, MPFR_DEFAULT_RND);
        mpfr_const_pi(divs, MPFR_DEFAULT_RND);
        break;
    }
    mpfr_mul(r->mf, r->mf, mult, MPFR_DEFAULT_RND);
    mpfr_div(r->mf, r->mf, divs, MPFR_DEFAULT_RND);

    mpfr_clear(mult);
    mpfr_clear(divs);
}