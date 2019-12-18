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
typedef  scalar_t__ mp_size ;
typedef  int mp_result ;
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 scalar_t__ MP_MAX_RADIX ; 
 scalar_t__ MP_MIN_RADIX ; 
 scalar_t__ MP_NEG ; 
 scalar_t__ MP_SIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int s_outlen (int /*<<< orphan*/ *,scalar_t__) ; 

mp_result
mp_int_string_len(mp_int z, mp_size radix)
{
	assert(z != NULL);
	assert(radix >= MP_MIN_RADIX && radix <= MP_MAX_RADIX);

	int			len = s_outlen(z, radix) + 1;	/* for terminator */

	/* Allow for sign marker on negatives */
	if (MP_SIGN(z) == MP_NEG)
		len += 1;

	return len;
}