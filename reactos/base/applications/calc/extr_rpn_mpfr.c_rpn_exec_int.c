#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpz_t ;
typedef  int /*<<< orphan*/  (* exec_call_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_5__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int /*<<< orphan*/  mpfr_get_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_set_z (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpn_exec_int(calc_number_t *r, calc_number_t *a, calc_number_t *b, exec_call_t cb)
{
    mpz_t ai, bi;

    mpz_init(ai);
    mpz_init(bi);
    mpfr_get_z(ai, a->mf, MPFR_DEFAULT_RND);
    mpfr_get_z(bi, b->mf, MPFR_DEFAULT_RND);
    cb(ai, ai, bi);
    mpfr_set_z(r->mf, ai, MPFR_DEFAULT_RND);
    mpz_clear(ai);
    mpz_clear(bi);
}