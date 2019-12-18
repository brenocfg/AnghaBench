#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
struct TYPE_28__ {void* sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int CMPZ (TYPE_1__*) ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_UNDEF ; 
 void* MP_ZPOS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* TEMP (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_abs (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mp_int_compare (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_copy (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mp_int_is_even (TYPE_1__*) ; 
 scalar_t__ mp_int_is_odd (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_set_value (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mp_int_sub (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_zero (TYPE_1__*) ; 
 int s_dp2k (TYPE_1__*) ; 
 int /*<<< orphan*/  s_qdiv (TYPE_1__*,int) ; 
 int /*<<< orphan*/  s_qmul (TYPE_1__*,int) ; 

mp_result
mp_int_egcd(mp_int a, mp_int b, mp_int c, mp_int x, mp_int y)
{
	assert(a != NULL && b != NULL && c != NULL && (x != NULL || y != NULL));

	mp_result	res = MP_OK;
	int			ca = CMPZ(a);
	int			cb = CMPZ(b);

	if (ca == 0 && cb == 0)
	{
		return MP_UNDEF;
	}
	else if (ca == 0)
	{
		if ((res = mp_int_abs(b, c)) != MP_OK)
			return res;
		mp_int_zero(x);
		(void) mp_int_set_value(y, 1);
		return MP_OK;
	}
	else if (cb == 0)
	{
		if ((res = mp_int_abs(a, c)) != MP_OK)
			return res;
		(void) mp_int_set_value(x, 1);
		mp_int_zero(y);
		return MP_OK;
	}

	/*
	 * Initialize temporaries: A:0, B:1, C:2, D:3, u:4, v:5, ou:6, ov:7
	 */
	DECLARE_TEMP(8);
	REQUIRE(mp_int_set_value(TEMP(0), 1));
	REQUIRE(mp_int_set_value(TEMP(3), 1));
	REQUIRE(mp_int_copy(a, TEMP(4)));
	REQUIRE(mp_int_copy(b, TEMP(5)));

	/* We will work with absolute values here */
	TEMP(4)->sign = MP_ZPOS;
	TEMP(5)->sign = MP_ZPOS;

	int			k = 0;

	{							/* Divide out common factors of 2 from u and v */
		int			div2_u = s_dp2k(TEMP(4)),
					div2_v = s_dp2k(TEMP(5));

		k = MIN(div2_u, div2_v);
		s_qdiv(TEMP(4), k);
		s_qdiv(TEMP(5), k);
	}

	REQUIRE(mp_int_copy(TEMP(4), TEMP(6)));
	REQUIRE(mp_int_copy(TEMP(5), TEMP(7)));

	for (;;)
	{
		while (mp_int_is_even(TEMP(4)))
		{
			s_qdiv(TEMP(4), 1);

			if (mp_int_is_odd(TEMP(0)) || mp_int_is_odd(TEMP(1)))
			{
				REQUIRE(mp_int_add(TEMP(0), TEMP(7), TEMP(0)));
				REQUIRE(mp_int_sub(TEMP(1), TEMP(6), TEMP(1)));
			}

			s_qdiv(TEMP(0), 1);
			s_qdiv(TEMP(1), 1);
		}

		while (mp_int_is_even(TEMP(5)))
		{
			s_qdiv(TEMP(5), 1);

			if (mp_int_is_odd(TEMP(2)) || mp_int_is_odd(TEMP(3)))
			{
				REQUIRE(mp_int_add(TEMP(2), TEMP(7), TEMP(2)));
				REQUIRE(mp_int_sub(TEMP(3), TEMP(6), TEMP(3)));
			}

			s_qdiv(TEMP(2), 1);
			s_qdiv(TEMP(3), 1);
		}

		if (mp_int_compare(TEMP(4), TEMP(5)) >= 0)
		{
			REQUIRE(mp_int_sub(TEMP(4), TEMP(5), TEMP(4)));
			REQUIRE(mp_int_sub(TEMP(0), TEMP(2), TEMP(0)));
			REQUIRE(mp_int_sub(TEMP(1), TEMP(3), TEMP(1)));
		}
		else
		{
			REQUIRE(mp_int_sub(TEMP(5), TEMP(4), TEMP(5)));
			REQUIRE(mp_int_sub(TEMP(2), TEMP(0), TEMP(2)));
			REQUIRE(mp_int_sub(TEMP(3), TEMP(1), TEMP(3)));
		}

		if (CMPZ(TEMP(4)) == 0)
		{
			if (x)
				REQUIRE(mp_int_copy(TEMP(2), x));
			if (y)
				REQUIRE(mp_int_copy(TEMP(3), y));
			if (c)
			{
				if (!s_qmul(TEMP(5), k))
				{
					REQUIRE(MP_MEMORY);
				}
				REQUIRE(mp_int_copy(TEMP(5), c));
			}

			break;
		}
	}

	CLEANUP_TEMP();
	return MP_OK;
}