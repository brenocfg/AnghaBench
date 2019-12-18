#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_small ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
struct TYPE_24__ {void* sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 scalar_t__ MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_UNDEF ; 
 void* MP_ZPOS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* TEMP (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_int_compare_unsigned (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_div (TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_expt (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_mul_value (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_neg (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_sub (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_sub_value (TYPE_1__*,int,TYPE_1__*) ; 

mp_result
mp_int_root(mp_int a, mp_small b, mp_int c)
{
	assert(a != NULL && c != NULL && b > 0);

	if (b == 1)
	{
		return mp_int_copy(a, c);
	}
	bool		flips = false;

	if (MP_SIGN(a) == MP_NEG)
	{
		if (b % 2 == 0)
		{
			return MP_UNDEF;	/* root does not exist for negative a with
								 * even b */
		}
		else
		{
			flips = true;
		}
	}

	DECLARE_TEMP(5);
	REQUIRE(mp_int_copy(a, TEMP(0)));
	REQUIRE(mp_int_copy(a, TEMP(1)));
	TEMP(0)->sign = MP_ZPOS;
	TEMP(1)->sign = MP_ZPOS;

	for (;;)
	{
		REQUIRE(mp_int_expt(TEMP(1), b, TEMP(2)));

		if (mp_int_compare_unsigned(TEMP(2), TEMP(0)) <= 0)
			break;

		REQUIRE(mp_int_sub(TEMP(2), TEMP(0), TEMP(2)));
		REQUIRE(mp_int_expt(TEMP(1), b - 1, TEMP(3)));
		REQUIRE(mp_int_mul_value(TEMP(3), b, TEMP(3)));
		REQUIRE(mp_int_div(TEMP(2), TEMP(3), TEMP(4), NULL));
		REQUIRE(mp_int_sub(TEMP(1), TEMP(4), TEMP(4)));

		if (mp_int_compare_unsigned(TEMP(1), TEMP(4)) == 0)
		{
			REQUIRE(mp_int_sub_value(TEMP(4), 1, TEMP(4)));
		}
		REQUIRE(mp_int_copy(TEMP(4), TEMP(1)));
	}

	REQUIRE(mp_int_copy(TEMP(1), c));

	/* If the original value of a was negative, flip the output sign. */
	if (flips)
		(void) mp_int_neg(c, c);	/* cannot fail */

	CLEANUP_TEMP();
	return MP_OK;
}