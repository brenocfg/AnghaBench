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
 scalar_t__ CMPZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 scalar_t__ MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_RANGE ; 
 scalar_t__ MP_SIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_UNDEF ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMP (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_int_compare_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_int_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_egcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

mp_result
mp_int_invmod(mp_int a, mp_int m, mp_int c)
{
	assert(a != NULL && m != NULL && c != NULL);

	if (CMPZ(a) == 0 || CMPZ(m) <= 0)
		return MP_RANGE;

	DECLARE_TEMP(2);

	REQUIRE(mp_int_egcd(a, m, TEMP(0), TEMP(1), NULL));

	if (mp_int_compare_value(TEMP(0), 1) != 0)
	{
		REQUIRE(MP_UNDEF);
	}

	/* It is first necessary to constrain the value to the proper range */
	REQUIRE(mp_int_mod(TEMP(1), m, TEMP(1)));

	/*
	 * Now, if 'a' was originally negative, the value we have is actually the
	 * magnitude of the negative representative; to get the positive value we
	 * have to subtract from the modulus.  Otherwise, the value is okay as it
	 * stands.
	 */
	if (MP_SIGN(a) == MP_NEG)
	{
		REQUIRE(mp_int_sub(m, TEMP(1), c));
	}
	else
	{
		REQUIRE(mp_int_copy(TEMP(1), c));
	}

	CLEANUP_TEMP();
	return MP_OK;
}