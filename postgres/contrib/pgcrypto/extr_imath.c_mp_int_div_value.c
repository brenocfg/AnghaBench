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
typedef  int /*<<< orphan*/  mpz_t ;
typedef  int /*<<< orphan*/  mp_small ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/  mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_TEMP () ; 
 int /*<<< orphan*/  DECLARE_TEMP (int) ; 
 int /*<<< orphan*/  MP_OK ; 
 int MP_VALUE_DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_to_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_fake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

mp_result
mp_int_div_value(mp_int a, mp_small value, mp_int q, mp_small *r)
{
	mpz_t		vtmp;
	mp_digit	vbuf[MP_VALUE_DIGITS(value)];

	s_fake(&vtmp, value, vbuf);

	DECLARE_TEMP(1);
	REQUIRE(mp_int_div(a, &vtmp, q, TEMP(0)));

	if (r)
		(void) mp_int_to_int(TEMP(0), r);	/* can't fail */

	CLEANUP_TEMP();
	return MP_OK;
}