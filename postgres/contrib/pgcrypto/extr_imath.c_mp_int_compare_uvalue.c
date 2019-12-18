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
typedef  int /*<<< orphan*/  mp_usmall ;
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 scalar_t__ MP_NEG ; 
 scalar_t__ MP_SIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int s_uvcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mp_int_compare_uvalue(mp_int z, mp_usmall uv)
{
	assert(z != NULL);

	if (MP_SIGN(z) == MP_NEG)
	{
		return -1;
	}
	else
	{
		return s_uvcmp(z, uv);
	}
}