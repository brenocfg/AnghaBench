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
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_div (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mp_result
mp_int_lcm(mp_int a, mp_int b, mp_int c)
{
	assert(a != NULL && b != NULL && c != NULL);

	/*
	 * Since a * b = gcd(a, b) * lcm(a, b), we can compute lcm(a, b) = (a /
	 * gcd(a, b)) * b.
	 *
	 * This formulation insures everything works even if the input variables
	 * share space.
	 */
	DECLARE_TEMP(1);
	REQUIRE(mp_int_gcd(a, b, TEMP(0)));
	REQUIRE(mp_int_div(a, TEMP(0), TEMP(0), NULL));
	REQUIRE(mp_int_mul(TEMP(0), b, TEMP(0)));
	REQUIRE(mp_int_copy(TEMP(0), c));

	CLEANUP_TEMP();
	return MP_OK;
}