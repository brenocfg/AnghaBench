#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
typedef  scalar_t__ mp_digit ;
struct TYPE_13__ {int used; int /*<<< orphan*/  sign; scalar_t__* digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  MP_DIGITS (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  s_pad (TYPE_1__*,int) ; 
 scalar_t__ s_uadd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int s_ucmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  s_usub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

mp_result
mp_int_add(mp_int a, mp_int b, mp_int c)
{
	assert(a != NULL && b != NULL && c != NULL);

	mp_size		ua = MP_USED(a);
	mp_size		ub = MP_USED(b);
	mp_size		max = MAX(ua, ub);

	if (MP_SIGN(a) == MP_SIGN(b))
	{
		/* Same sign -- add magnitudes, preserve sign of addends */
		if (!s_pad(c, max))
			return MP_MEMORY;

		mp_digit	carry = s_uadd(MP_DIGITS(a), MP_DIGITS(b), MP_DIGITS(c), ua, ub);
		mp_size		uc = max;

		if (carry)
		{
			if (!s_pad(c, max + 1))
				return MP_MEMORY;

			c->digits[max] = carry;
			++uc;
		}

		c->used = uc;
		c->sign = a->sign;

	}
	else
	{
		/* Different signs -- subtract magnitudes, preserve sign of greater */
		int			cmp = s_ucmp(a, b); /* magnitude comparision, sign ignored */

		/*
		 * Set x to max(a, b), y to min(a, b) to simplify later code. A
		 * special case yields zero for equal magnitudes.
		 */
		mp_int		x,
					y;

		if (cmp == 0)
		{
			mp_int_zero(c);
			return MP_OK;
		}
		else if (cmp < 0)
		{
			x = b;
			y = a;
		}
		else
		{
			x = a;
			y = b;
		}

		if (!s_pad(c, MP_USED(x)))
			return MP_MEMORY;

		/* Subtract smaller from larger */
		s_usub(MP_DIGITS(x), MP_DIGITS(y), MP_DIGITS(c), MP_USED(x), MP_USED(y));
		c->used = x->used;
		CLAMP(c);

		/* Give result the sign of the larger */
		c->sign = x->sign;
	}

	return MP_OK;
}