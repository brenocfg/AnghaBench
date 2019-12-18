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
typedef  scalar_t__ mp_small ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_RANGE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 unsigned int labs (scalar_t__) ; 
 int /*<<< orphan*/  mp_int_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_int_set_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_int_sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

mp_result
mp_int_expt_value(mp_small a, mp_small b, mp_int c)
{
	assert(c != NULL);
	if (b < 0)
		return MP_RANGE;

	DECLARE_TEMP(1);
	REQUIRE(mp_int_set_value(TEMP(0), a));

	(void) mp_int_set_value(c, 1);
	unsigned int v = labs(b);

	while (v != 0)
	{
		if (v & 1)
		{
			REQUIRE(mp_int_mul(c, TEMP(0), c));
		}

		v >>= 1;
		if (v == 0)
			break;

		REQUIRE(mp_int_sqr(TEMP(0), TEMP(0)));
	}

	CLEANUP_TEMP();
	return MP_OK;
}