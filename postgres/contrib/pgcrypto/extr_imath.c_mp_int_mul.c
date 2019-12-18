#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_sign ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;
struct TYPE_12__ {int alloc; int used; int /*<<< orphan*/  sign; int /*<<< orphan*/ * digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/ * MP_DIGITS (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_ZPOS ; 
 int /*<<< orphan*/  ZERO (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int default_precision ; 
 scalar_t__ mp_int_compare_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_zero (TYPE_1__*) ; 
 int /*<<< orphan*/ * s_alloc (int) ; 
 int /*<<< orphan*/  s_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_kmul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  s_pad (TYPE_1__*,int) ; 
 int s_round_prec (int) ; 

mp_result
mp_int_mul(mp_int a, mp_int b, mp_int c)
{
	assert(a != NULL && b != NULL && c != NULL);

	/* If either input is zero, we can shortcut multiplication */
	if (mp_int_compare_zero(a) == 0 || mp_int_compare_zero(b) == 0)
	{
		mp_int_zero(c);
		return MP_OK;
	}

	/* Output is positive if inputs have same sign, otherwise negative */
	mp_sign		osign = (MP_SIGN(a) == MP_SIGN(b)) ? MP_ZPOS : MP_NEG;

	/*
	 * If the output is not identical to any of the inputs, we'll write the
	 * results directly; otherwise, allocate a temporary space.
	 */
	mp_size		ua = MP_USED(a);
	mp_size		ub = MP_USED(b);
	mp_size		osize = MAX(ua, ub);

	osize = 4 * ((osize + 1) / 2);

	mp_digit   *out;
	mp_size		p = 0;

	if (c == a || c == b)
	{
		p = MAX(s_round_prec(osize), default_precision);

		if ((out = s_alloc(p)) == NULL)
			return MP_MEMORY;
	}
	else
	{
		if (!s_pad(c, osize))
			return MP_MEMORY;

		out = MP_DIGITS(c);
	}
	ZERO(out, osize);

	if (!s_kmul(MP_DIGITS(a), MP_DIGITS(b), out, ua, ub))
		return MP_MEMORY;

	/*
	 * If we allocated a new buffer, get rid of whatever memory c was already
	 * using, and fix up its fields to reflect that.
	 */
	if (out != MP_DIGITS(c))
	{
		if ((void *) MP_DIGITS(c) != (void *) c)
			s_free(MP_DIGITS(c));
		c->digits = out;
		c->alloc = p;
	}

	c->used = osize;			/* might not be true, but we'll fix it ... */
	CLAMP(c);					/* ... right here */
	c->sign = osign;

	return MP_OK;
}