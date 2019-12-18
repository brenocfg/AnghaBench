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
 int MP_VALUE_DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_init_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_fake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

mp_result
mp_int_init_value(mp_int z, mp_small value)
{
	mpz_t		vtmp;
	mp_digit	vbuf[MP_VALUE_DIGITS(value)];

	s_fake(&vtmp, value, vbuf);
	return mp_int_init_copy(z, &vtmp);
}