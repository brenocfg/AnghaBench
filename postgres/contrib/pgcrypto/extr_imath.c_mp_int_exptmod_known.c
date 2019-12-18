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
typedef  int /*<<< orphan*/  mp_result ;
typedef  scalar_t__ mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 scalar_t__ CMPZ (scalar_t__) ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  GROW (scalar_t__,int) ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_RANGE ; 
 int /*<<< orphan*/  MP_UNDEF ; 
 int MP_USED (scalar_t__) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMP (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mp_int_mod (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  s_embar (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

mp_result
mp_int_exptmod_known(mp_int a, mp_int b, mp_int m, mp_int mu,
					 mp_int c)
{
	assert(a && b && m && c);

	/* Zero moduli and negative exponents are not considered. */
	if (CMPZ(m) == 0)
		return MP_UNDEF;
	if (CMPZ(b) < 0)
		return MP_RANGE;

	DECLARE_TEMP(2);
	mp_size		um = MP_USED(m);

	REQUIRE(GROW(TEMP(0), 2 * um));

	mp_int		s;

	if (c == b || c == m)
	{
		REQUIRE(GROW(TEMP(1), 2 * um));
		s = TEMP(1);
	}
	else
	{
		s = c;
	}

	REQUIRE(mp_int_mod(a, m, TEMP(0)));
	REQUIRE(s_embar(TEMP(0), b, m, mu, s));
	REQUIRE(mp_int_copy(s, c));

	CLEANUP_TEMP();
	return MP_OK;
}