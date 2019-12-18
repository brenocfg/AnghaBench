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
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 scalar_t__ CMPZ (int /*<<< orphan*/ ) ; 
 int MP_DIGIT_BIT ; 
 scalar_t__ MP_OK ; 
 int MP_USED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMUL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_int_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_int_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_qdiv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_qmod (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_qsub (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
s_reduce(mp_int x, mp_int m, mp_int mu, mp_int q1, mp_int q2)
{
	mp_size		um = MP_USED(m),
				umb_p1,
				umb_m1;

	umb_p1 = (um + 1) * MP_DIGIT_BIT;
	umb_m1 = (um - 1) * MP_DIGIT_BIT;

	if (mp_int_copy(x, q1) != MP_OK)
		return 0;

	/* Compute q2 = floor((floor(x / b^(k-1)) * mu) / b^(k+1)) */
	s_qdiv(q1, umb_m1);
	UMUL(q1, mu, q2);
	s_qdiv(q2, umb_p1);

	/* Set x = x mod b^(k+1) */
	s_qmod(x, umb_p1);

	/*
	 * Now, q is a guess for the quotient a / m. Compute x - q * m mod
	 * b^(k+1), replacing x.  This may be off by a factor of 2m, but no more
	 * than that.
	 */
	UMUL(q2, m, q1);
	s_qmod(q1, umb_p1);
	(void) mp_int_sub(x, q1, x);	/* can't fail */

	/*
	 * The result may be < 0; if it is, add b^(k+1) to pin it in the proper
	 * range.
	 */
	if ((CMPZ(x) < 0) && !s_qsub(x, umb_p1))
		return 0;

	/*
	 * If x > m, we need to back it off until it is in range.  This will be
	 * required at most twice.
	 */
	if (mp_int_compare(x, m) >= 0)
	{
		(void) mp_int_sub(x, m, x);
		if (mp_int_compare(x, m) >= 0)
		{
			(void) mp_int_sub(x, m, x);
		}
	}

	/* At this point, x has been properly reduced. */
	return 1;
}