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
typedef  int /*<<< orphan*/  mp_size ;
typedef  scalar_t__ mp_result ;
typedef  int /*<<< orphan*/ * mp_int ;

/* Variables and functions */
 scalar_t__ MP_MEMORY ; 
 scalar_t__ MP_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_int_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ s_qmul (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mp_result
mp_int_mul_pow2(mp_int a, mp_small p2, mp_int c)
{
	assert(a != NULL && c != NULL && p2 >= 0);

	mp_result	res = mp_int_copy(a, c);

	if (res != MP_OK)
		return res;

	if (s_qmul(c, (mp_size) p2))
	{
		return MP_OK;
	}
	else
	{
		return MP_MEMORY;
	}
}