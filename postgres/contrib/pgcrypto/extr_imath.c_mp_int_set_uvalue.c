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
typedef  int /*<<< orphan*/  mp_usmall ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/  mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int MP_VALUE_DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_int_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_ufake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

mp_result
mp_int_set_uvalue(mp_int z, mp_usmall uvalue)
{
	mpz_t		vtmp;
	mp_digit	vbuf[MP_VALUE_DIGITS(uvalue)];

	s_ufake(&vtmp, uvalue, vbuf);
	return mp_int_copy(&vtmp, z);
}