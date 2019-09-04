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
typedef  int /*<<< orphan*/  mpz_t ;
struct TYPE_3__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int /*<<< orphan*/  mpfr_get_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_set_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_com (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_init (int /*<<< orphan*/ ) ; 

void rpn_not(calc_number_t *c)
{
    mpz_t a;

    mpz_init(a);
    mpfr_get_z(a, c->mf, MPFR_DEFAULT_RND);
    mpz_com(a, a);
    mpfr_set_z(c->mf, a, MPFR_DEFAULT_RND);
    mpz_clear(a);
}