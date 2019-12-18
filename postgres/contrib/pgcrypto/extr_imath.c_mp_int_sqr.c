#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;
struct TYPE_8__ {int alloc; int used; int /*<<< orphan*/  sign; int /*<<< orphan*/ * digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MP_DIGITS (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_OK ; 
 int MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_ZPOS ; 
 int /*<<< orphan*/  ZERO (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  default_precision ; 
 int /*<<< orphan*/ * s_alloc (int) ; 
 int /*<<< orphan*/  s_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_ksqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_pad (TYPE_1__*,int) ; 
 int s_round_prec (int) ; 

mp_result
mp_int_sqr(mp_int a, mp_int c)
{
	assert(a != NULL && c != NULL);

	/* Get a temporary buffer big enough to hold the result */
	mp_size		osize = (mp_size) 4 * ((MP_USED(a) + 1) / 2);
	mp_size		p = 0;
	mp_digit   *out;

	if (a == c)
	{
		p = s_round_prec(osize);
		p = MAX(p, default_precision);

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

	s_ksqr(MP_DIGITS(a), out, MP_USED(a));

	/*
	 * Get rid of whatever memory c was already using, and fix up its fields
	 * to reflect the new digit array it's using
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
	c->sign = MP_ZPOS;

	return MP_OK;
}