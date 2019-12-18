#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_size ;
typedef  scalar_t__ mp_sign ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
struct TYPE_19__ {int* digits; void* sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 scalar_t__ CMPZ (TYPE_1__*) ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 void* MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_UNDEF ; 
 void* MP_ZPOS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* TEMP (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_zero (TYPE_1__*) ; 
 int s_isp2 (TYPE_1__*) ; 
 int /*<<< orphan*/  s_qdiv (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_qmod (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int s_ucmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  s_udiv_knuth (TYPE_1__*,TYPE_1__*) ; 

mp_result
mp_int_div(mp_int a, mp_int b, mp_int q, mp_int r)
{
	assert(a != NULL && b != NULL && q != r);

	int			cmp;
	mp_result	res = MP_OK;
	mp_int		qout,
				rout;
	mp_sign		sa = MP_SIGN(a);
	mp_sign		sb = MP_SIGN(b);

	if (CMPZ(b) == 0)
	{
		return MP_UNDEF;
	}
	else if ((cmp = s_ucmp(a, b)) < 0)
	{
		/*
		 * If |a| < |b|, no division is required: q = 0, r = a
		 */
		if (r && (res = mp_int_copy(a, r)) != MP_OK)
			return res;

		if (q)
			mp_int_zero(q);

		return MP_OK;
	}
	else if (cmp == 0)
	{
		/*
		 * If |a| = |b|, no division is required: q = 1 or -1, r = 0
		 */
		if (r)
			mp_int_zero(r);

		if (q)
		{
			mp_int_zero(q);
			q->digits[0] = 1;

			if (sa != sb)
				q->sign = MP_NEG;
		}

		return MP_OK;
	}

	/*
	 * When |a| > |b|, real division is required.  We need someplace to store
	 * quotient and remainder, but q and r are allowed to be NULL or to
	 * overlap with the inputs.
	 */
	DECLARE_TEMP(2);
	int			lg;

	if ((lg = s_isp2(b)) < 0)
	{
		if (q && b != q)
		{
			REQUIRE(mp_int_copy(a, q));
			qout = q;
		}
		else
		{
			REQUIRE(mp_int_copy(a, TEMP(0)));
			qout = TEMP(0);
		}

		if (r && a != r)
		{
			REQUIRE(mp_int_copy(b, r));
			rout = r;
		}
		else
		{
			REQUIRE(mp_int_copy(b, TEMP(1)));
			rout = TEMP(1);
		}

		REQUIRE(s_udiv_knuth(qout, rout));
	}
	else
	{
		if (q)
			REQUIRE(mp_int_copy(a, q));
		if (r)
			REQUIRE(mp_int_copy(a, r));

		if (q)
			s_qdiv(q, (mp_size) lg);
		qout = q;
		if (r)
			s_qmod(r, (mp_size) lg);
		rout = r;
	}

	/* Recompute signs for output */
	if (rout)
	{
		rout->sign = sa;
		if (CMPZ(rout) == 0)
			rout->sign = MP_ZPOS;
	}
	if (qout)
	{
		qout->sign = (sa == sb) ? MP_ZPOS : MP_NEG;
		if (CMPZ(qout) == 0)
			qout->sign = MP_ZPOS;
	}

	if (q)
		REQUIRE(mp_int_copy(qout, q));
	if (r)
		REQUIRE(mp_int_copy(rout, r));
	CLEANUP_TEMP();
	return res;
}