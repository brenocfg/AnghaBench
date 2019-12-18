#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/  mp_int ;
typedef  int mp_digit ;
struct TYPE_10__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  GROW (TYPE_1__*,int) ; 
 int* MP_DIGITS (int /*<<< orphan*/ ) ; 
 int MP_DIGIT_BIT ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int MP_USED (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_ZPOS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* TEMP (int) ; 
 int /*<<< orphan*/  UMUL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  USQR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_reduce (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static mp_result
s_embar(mp_int a, mp_int b, mp_int m, mp_int mu, mp_int c)
{
	mp_digit	umu = MP_USED(mu);
	mp_digit   *db = MP_DIGITS(b);
	mp_digit   *dbt = db + MP_USED(b) - 1;

	DECLARE_TEMP(3);
	REQUIRE(GROW(TEMP(0), 4 * umu));
	REQUIRE(GROW(TEMP(1), 4 * umu));
	REQUIRE(GROW(TEMP(2), 4 * umu));
	ZERO(TEMP(0)->digits, TEMP(0)->alloc);
	ZERO(TEMP(1)->digits, TEMP(1)->alloc);
	ZERO(TEMP(2)->digits, TEMP(2)->alloc);

	(void) mp_int_set_value(c, 1);

	/* Take care of low-order digits */
	while (db < dbt)
	{
		mp_digit	d = *db;

		for (int i = MP_DIGIT_BIT; i > 0; --i, d >>= 1)
		{
			if (d & 1)
			{
				/* The use of a second temporary avoids allocation */
				UMUL(c, a, TEMP(0));
				if (!s_reduce(TEMP(0), m, mu, TEMP(1), TEMP(2)))
				{
					REQUIRE(MP_MEMORY);
				}
				mp_int_copy(TEMP(0), c);
			}

			USQR(a, TEMP(0));
			assert(MP_SIGN(TEMP(0)) == MP_ZPOS);
			if (!s_reduce(TEMP(0), m, mu, TEMP(1), TEMP(2)))
			{
				REQUIRE(MP_MEMORY);
			}
			assert(MP_SIGN(TEMP(0)) == MP_ZPOS);
			mp_int_copy(TEMP(0), a);
		}

		++db;
	}

	/* Take care of highest-order digit */
	mp_digit	d = *dbt;

	for (;;)
	{
		if (d & 1)
		{
			UMUL(c, a, TEMP(0));
			if (!s_reduce(TEMP(0), m, mu, TEMP(1), TEMP(2)))
			{
				REQUIRE(MP_MEMORY);
			}
			mp_int_copy(TEMP(0), c);
		}

		d >>= 1;
		if (!d)
			break;

		USQR(a, TEMP(0));
		if (!s_reduce(TEMP(0), m, mu, TEMP(1), TEMP(2)))
		{
			REQUIRE(MP_MEMORY);
		}
		(void) mp_int_copy(TEMP(0), a);
	}

	CLEANUP_TEMP();
	return MP_OK;
}