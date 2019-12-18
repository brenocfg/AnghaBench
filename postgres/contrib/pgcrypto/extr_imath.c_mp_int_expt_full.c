#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
typedef  int mp_digit ;
struct TYPE_11__ {int* digits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 unsigned int MP_DIGIT_BIT ; 
 scalar_t__ MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_RANGE ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 unsigned int MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_mul (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_int_set_value (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mp_int_sqr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mp_result
mp_int_expt_full(mp_int a, mp_int b, mp_int c)
{
	assert(a != NULL && b != NULL && c != NULL);
	if (MP_SIGN(b) == MP_NEG)
		return MP_RANGE;

	DECLARE_TEMP(1);
	REQUIRE(mp_int_copy(a, TEMP(0)));

	(void) mp_int_set_value(c, 1);
	for (unsigned ix = 0; ix < MP_USED(b); ++ix)
	{
		mp_digit	d = b->digits[ix];

		for (unsigned jx = 0; jx < MP_DIGIT_BIT; ++jx)
		{
			if (d & 1)
			{
				REQUIRE(mp_int_mul(c, TEMP(0), c));
			}

			d >>= 1;
			if (d == 0 && ix + 1 == MP_USED(b))
				break;
			REQUIRE(mp_int_sqr(TEMP(0), TEMP(0)));
		}
	}

	CLEANUP_TEMP();
	return MP_OK;
}