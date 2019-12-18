#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int* digits; int used; int /*<<< orphan*/  alloc; void* sign; } ;
typedef  TYPE_1__ mpz_t ;
typedef  int mp_word ;
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (TYPE_1__*) ; 
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  GROW (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MP_ALLOC (TYPE_1__*) ; 
 int* MP_DIGITS (TYPE_1__*) ; 
 int MP_DIGIT_BIT ; 
 int MP_DIGIT_MAX ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 int /*<<< orphan*/  MP_OK ; 
 int MP_USED (TYPE_1__*) ; 
 void* MP_ZPOS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* TEMP (int) ; 
 int /*<<< orphan*/  ZERO (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_set_value (TYPE_1__*,int) ; 
 int /*<<< orphan*/  s_dbmul (int*,int,int*,int) ; 
 int s_ddiv (TYPE_1__*,int) ; 
 int s_norm (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  s_pad (TYPE_1__*,int) ; 
 int /*<<< orphan*/  s_qdiv (TYPE_1__*,int) ; 
 scalar_t__ s_ucmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  s_usub (int*,int*,int*,int,int) ; 

__attribute__((used)) static mp_result
s_udiv_knuth(mp_int u, mp_int v)
{
	/* Force signs to positive */
	u->sign = MP_ZPOS;
	v->sign = MP_ZPOS;

	/* Use simple division algorithm when v is only one digit long */
	if (MP_USED(v) == 1)
	{
		mp_digit	d,
					rem;

		d = v->digits[0];
		rem = s_ddiv(u, d);
		mp_int_set_value(v, rem);
		return MP_OK;
	}

	/*
	 * Algorithm D
	 *
	 * The n and m variables are defined as used by Knuth. u is an n digit
	 * number with digits u_{n-1}..u_0. v is an n+m digit number with digits
	 * from v_{m+n-1}..v_0. We require that n > 1 and m >= 0
	 */
	mp_size		n = MP_USED(v);
	mp_size		m = MP_USED(u) - n;

	assert(n > 1);
	/* assert(m >= 0) follows because m is unsigned. */

	/*
	 * D1: Normalize. The normalization step provides the necessary condition
	 * for Theorem B, which states that the quotient estimate for q_j, call it
	 * qhat
	 *
	 * qhat = u_{j+n}u_{j+n-1} / v_{n-1}
	 *
	 * is bounded by
	 *
	 * qhat - 2 <= q_j <= qhat.
	 *
	 * That is, qhat is always greater than the actual quotient digit q, and
	 * it is never more than two larger than the actual quotient digit.
	 */
	int			k = s_norm(u, v);

	/*
	 * Extend size of u by one if needed.
	 *
	 * The algorithm begins with a value of u that has one more digit of
	 * input. The normalization step sets u_{m+n}..u_0 = 2^k * u_{m+n-1}..u_0.
	 * If the multiplication did not increase the number of digits of u, we
	 * need to add a leading zero here.
	 */
	if (k == 0 || MP_USED(u) != m + n + 1)
	{
		if (!s_pad(u, m + n + 1))
			return MP_MEMORY;
		u->digits[m + n] = 0;
		u->used = m + n + 1;
	}

	/*
	 * Add a leading 0 to v.
	 *
	 * The multiplication in step D4 multiplies qhat * 0v_{n-1}..v_0.  We need
	 * to add the leading zero to v here to ensure that the multiplication
	 * will produce the full n+1 digit result.
	 */
	if (!s_pad(v, n + 1))
		return MP_MEMORY;
	v->digits[n] = 0;

	/*
	 * Initialize temporary variables q and t. q allocates space for m+1
	 * digits to store the quotient digits t allocates space for n+1 digits to
	 * hold the result of q_j*v
	 */
	DECLARE_TEMP(2);
	REQUIRE(GROW(TEMP(0), m + 1));
	REQUIRE(GROW(TEMP(1), n + 1));

	/* D2: Initialize j */
	int			j = m;
	mpz_t		r;

	r.digits = MP_DIGITS(u) + j;	/* The contents of r are shared with u */
	r.used = n + 1;
	r.sign = MP_ZPOS;
	r.alloc = MP_ALLOC(u);
	ZERO(TEMP(1)->digits, TEMP(1)->alloc);

	/* Calculate the m+1 digits of the quotient result */
	for (; j >= 0; j--)
	{
		/* D3: Calculate q' */
		/* r->digits is aligned to position j of the number u */
		mp_word		pfx,
					qhat;

		pfx = r.digits[n];
		pfx <<= MP_DIGIT_BIT / 2;
		pfx <<= MP_DIGIT_BIT / 2;
		pfx |= r.digits[n - 1]; /* pfx = u_{j+n}{j+n-1} */

		qhat = pfx / v->digits[n - 1];

		/*
		 * Check to see if qhat > b, and decrease qhat if so. Theorem B
		 * guarantess that qhat is at most 2 larger than the actual value, so
		 * it is possible that qhat is greater than the maximum value that
		 * will fit in a digit
		 */
		if (qhat > MP_DIGIT_MAX)
			qhat = MP_DIGIT_MAX;

		/*
		 * D4,D5,D6: Multiply qhat * v and test for a correct value of q
		 *
		 * We proceed a bit different than the way described by Knuth. This
		 * way is simpler but less efficent. Instead of doing the multiply and
		 * subtract then checking for underflow, we first do the multiply of
		 * qhat * v and see if it is larger than the current remainder r. If
		 * it is larger, we decrease qhat by one and try again. We may need to
		 * decrease qhat one more time before we get a value that is smaller
		 * than r.
		 *
		 * This way is less efficent than Knuth becuase we do more multiplies,
		 * but we do not need to worry about underflow this way.
		 */
		/* t = qhat * v */
		s_dbmul(MP_DIGITS(v), (mp_digit) qhat, TEMP(1)->digits, n + 1);
		TEMP(1)->used = n + 1;
		CLAMP(TEMP(1));

		/* Clamp r for the comparison. Comparisons do not like leading zeros. */
		CLAMP(&r);
		if (s_ucmp(TEMP(1), &r) > 0)
		{						/* would the remainder be negative? */
			qhat -= 1;			/* try a smaller q */
			s_dbmul(MP_DIGITS(v), (mp_digit) qhat, TEMP(1)->digits, n + 1);
			TEMP(1)->used = n + 1;
			CLAMP(TEMP(1));
			if (s_ucmp(TEMP(1), &r) > 0)
			{					/* would the remainder be negative? */
				assert(qhat > 0);
				qhat -= 1;		/* try a smaller q */
				s_dbmul(MP_DIGITS(v), (mp_digit) qhat, TEMP(1)->digits, n + 1);
				TEMP(1)->used = n + 1;
				CLAMP(TEMP(1));
			}
			assert(s_ucmp(TEMP(1), &r) <= 0 && "The mathematics failed us.");
		}

		/*
		 * Unclamp r. The D algorithm expects r = u_{j+n}..u_j to always be
		 * n+1 digits long.
		 */
		r.used = n + 1;

		/*
		 * D4: Multiply and subtract
		 *
		 * Note: The multiply was completed above so we only need to subtract
		 * here.
		 */
		s_usub(r.digits, TEMP(1)->digits, r.digits, r.used, TEMP(1)->used);

		/*
		 * D5: Test remainder
		 *
		 * Note: Not needed because we always check that qhat is the correct
		 * value before performing the subtract.  Value cast to mp_digit to
		 * prevent warning, qhat has been clamped to MP_DIGIT_MAX
		 */
		TEMP(0)->digits[j] = (mp_digit) qhat;

		/*
		 * D6: Add back Note: Not needed because we always check that qhat is
		 * the correct value before performing the subtract.
		 */

		/* D7: Loop on j */
		r.digits--;
		ZERO(TEMP(1)->digits, TEMP(1)->alloc);
	}

	/* Get rid of leading zeros in q */
	TEMP(0)->used = m + 1;
	CLAMP(TEMP(0));

	/* Denormalize the remainder */
	CLAMP(u);					/* use u here because the r.digits pointer is
								 * off-by-one */
	if (k != 0)
		s_qdiv(u, k);

	mp_int_copy(u, v);			/* ok:  0 <= r < v */
	mp_int_copy(TEMP(0), u);	/* ok:  q <= u     */

	CLEANUP_TEMP();
	return MP_OK;
}