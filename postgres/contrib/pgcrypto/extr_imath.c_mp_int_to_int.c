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
typedef  int mp_usmall ;
typedef  int mp_small ;
typedef  scalar_t__ mp_sign ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/ * mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/ * MP_DIGITS (int /*<<< orphan*/ *) ; 
 int MP_DIGIT_BIT ; 
 scalar_t__ MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 int /*<<< orphan*/  MP_RANGE ; 
 scalar_t__ MP_SIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_SMALL_MAX ; 
 int /*<<< orphan*/  MP_SMALL_MIN ; 
 int MP_USED (int /*<<< orphan*/ *) ; 
 scalar_t__ MP_ZPOS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_int_compare_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mp_result
mp_int_to_int(mp_int z, mp_small *out)
{
	assert(z != NULL);

	/* Make sure the value is representable as a small integer */
	mp_sign		sz = MP_SIGN(z);

	if ((sz == MP_ZPOS && mp_int_compare_value(z, MP_SMALL_MAX) > 0) ||
		mp_int_compare_value(z, MP_SMALL_MIN) < 0)
	{
		return MP_RANGE;
	}

	mp_usmall	uz = MP_USED(z);
	mp_digit   *dz = MP_DIGITS(z) + uz - 1;
	mp_small	uv = 0;

	while (uz > 0)
	{
		uv <<= MP_DIGIT_BIT / 2;
		uv = (uv << (MP_DIGIT_BIT / 2)) | *dz--;
		--uz;
	}

	if (out)
		*out = (mp_small) ((sz == MP_NEG) ? -uv : uv);

	return MP_OK;
}