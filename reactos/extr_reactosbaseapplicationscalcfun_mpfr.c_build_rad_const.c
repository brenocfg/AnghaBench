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
typedef  int /*<<< orphan*/  mpfr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int /*<<< orphan*/  mpfr_const_pi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_div_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_mul_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_rad_const(
    mpfr_t *mp_pi,
    mpfr_t *mp_pi_2,
    mpfr_t *mp_3_pi_2,
    mpfr_t *mp_2_pi)
{
    mpfr_init(*mp_pi);
    mpfr_init(*mp_pi_2);
    mpfr_init(*mp_3_pi_2);
    mpfr_init(*mp_2_pi);
    mpfr_const_pi(*mp_pi, MPFR_DEFAULT_RND);
    mpfr_div_ui(*mp_pi_2, *mp_pi, 2, MPFR_DEFAULT_RND);
    mpfr_mul_ui(*mp_3_pi_2, *mp_pi, 3, MPFR_DEFAULT_RND);
    mpfr_div_ui(*mp_3_pi_2, *mp_3_pi_2, 2, MPFR_DEFAULT_RND);
    mpfr_mul_ui(*mp_2_pi, *mp_pi, 2, MPFR_DEFAULT_RND);
}