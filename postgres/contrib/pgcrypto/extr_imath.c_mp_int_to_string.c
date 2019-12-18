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
typedef  int /*<<< orphan*/  mpz_t ;
typedef  scalar_t__ mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/ * mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 scalar_t__ CMPZ (int /*<<< orphan*/ *) ; 
 scalar_t__ MP_MAX_RADIX ; 
 scalar_t__ MP_MIN_RADIX ; 
 scalar_t__ MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_TRUNC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_init_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_ddiv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* s_val2ch (int /*<<< orphan*/ ,int) ; 

mp_result
mp_int_to_string(mp_int z, mp_size radix, char *str, int limit)
{
	assert(z != NULL && str != NULL && limit >= 2);
	assert(radix >= MP_MIN_RADIX && radix <= MP_MAX_RADIX);

	int			cmp = 0;

	if (CMPZ(z) == 0)
	{
		*str++ = s_val2ch(0, 1);
	}
	else
	{
		mp_result	res;
		mpz_t		tmp;
		char	   *h,
				   *t;

		if ((res = mp_int_init_copy(&tmp, z)) != MP_OK)
			return res;

		if (MP_SIGN(z) == MP_NEG)
		{
			*str++ = '-';
			--limit;
		}
		h = str;

		/* Generate digits in reverse order until finished or limit reached */
		for ( /* */ ; limit > 0; --limit)
		{
			mp_digit	d;

			if ((cmp = CMPZ(&tmp)) == 0)
				break;

			d = s_ddiv(&tmp, (mp_digit) radix);
			*str++ = s_val2ch(d, 1);
		}
		t = str - 1;

		/* Put digits back in correct output order */
		while (h < t)
		{
			char		tc = *h;

			*h++ = *t;
			*t-- = tc;
		}

		mp_int_clear(&tmp);
	}

	*str = '\0';
	if (cmp == 0)
	{
		return MP_OK;
	}
	else
	{
		return MP_TRUNC;
	}
}