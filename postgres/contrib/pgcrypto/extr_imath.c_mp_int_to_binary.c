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
typedef  int /*<<< orphan*/  mp_result ;
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 scalar_t__ MP_NEG ; 
 scalar_t__ MP_SIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  s_2comp (unsigned char*,int) ; 
 int /*<<< orphan*/  s_tobin (int /*<<< orphan*/ *,unsigned char*,int*,int const) ; 

mp_result
mp_int_to_binary(mp_int z, unsigned char *buf, int limit)
{
	static const int PAD_FOR_2C = 1;

	assert(z != NULL && buf != NULL);

	int			limpos = limit;
	mp_result	res = s_tobin(z, buf, &limpos, PAD_FOR_2C);

	if (MP_SIGN(z) == MP_NEG)
		s_2comp(buf, limpos);

	return res;
}