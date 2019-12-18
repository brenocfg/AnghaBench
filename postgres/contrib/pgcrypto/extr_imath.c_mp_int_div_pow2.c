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
 scalar_t__ MP_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_int_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_qdiv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_qmod (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mp_result
mp_int_div_pow2(mp_int a, mp_small p2, mp_int q, mp_int r)
{
	assert(a != NULL && p2 >= 0 && q != r);

	mp_result	res = MP_OK;

	if (q != NULL && (res = mp_int_copy(a, q)) == MP_OK)
	{
		s_qdiv(q, (mp_size) p2);
	}

	if (res == MP_OK && r != NULL && (res = mp_int_copy(a, r)) == MP_OK)
	{
		s_qmod(r, (mp_size) p2);
	}

	return res;
}