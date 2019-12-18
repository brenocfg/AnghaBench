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
typedef  scalar_t__ mp_sign ;
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 scalar_t__ MP_SIGN (int /*<<< orphan*/ *) ; 
 scalar_t__ MP_ZPOS ; 
 int /*<<< orphan*/  assert (int) ; 
 int s_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
mp_int_compare(mp_int a, mp_int b)
{
	assert(a != NULL && b != NULL);

	mp_sign		sa = MP_SIGN(a);

	if (sa == MP_SIGN(b))
	{
		int			cmp = s_ucmp(a, b);

		/*
		 * If they're both zero or positive, the normal comparison applies; if
		 * both negative, the sense is reversed.
		 */
		if (sa == MP_ZPOS)
		{
			return cmp;
		}
		else
		{
			return -cmp;
		}
	}
	else if (sa == MP_ZPOS)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}