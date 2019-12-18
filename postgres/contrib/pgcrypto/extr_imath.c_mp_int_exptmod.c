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
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 scalar_t__ CMPZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  GROW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_RANGE ; 
 int /*<<< orphan*/  MP_UNDEF ; 
 int MP_USED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TEMP (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_brmu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_embar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

mp_result
mp_int_exptmod(mp_int a, mp_int b, mp_int m, mp_int c)
{
	assert(a != NULL && b != NULL && c != NULL && m != NULL);

	/* Zero moduli and negative exponents are not considered. */
	if (CMPZ(m) == 0)
		return MP_UNDEF;
	if (CMPZ(b) < 0)
		return MP_RANGE;

	mp_size		um = MP_USED(m);

	DECLARE_TEMP(3);
	REQUIRE(GROW(TEMP(0), 2 * um));
	REQUIRE(GROW(TEMP(1), 2 * um));

	mp_int		s;

	if (c == b || c == m)
	{
		REQUIRE(GROW(TEMP(2), 2 * um));
		s = TEMP(2);
	}
	else
	{
		s = c;
	}

	REQUIRE(mp_int_mod(a, m, TEMP(0)));
	REQUIRE(s_brmu(TEMP(1), m));
	REQUIRE(s_embar(TEMP(0), b, m, TEMP(1), s));
	REQUIRE(mp_int_copy(s, c));

	CLEANUP_TEMP();
	return MP_OK;
}