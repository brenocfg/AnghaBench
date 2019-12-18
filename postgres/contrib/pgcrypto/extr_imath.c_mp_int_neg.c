#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
struct TYPE_8__ {scalar_t__ sign; } ;

/* Variables and functions */
 scalar_t__ CMPZ (TYPE_1__*) ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_copy (TYPE_1__*,TYPE_1__*) ; 

mp_result
mp_int_neg(mp_int a, mp_int c)
{
	assert(a != NULL && c != NULL);

	mp_result	res;

	if ((res = mp_int_copy(a, c)) != MP_OK)
		return res;

	if (CMPZ(c) != 0)
		c->sign = 1 - MP_SIGN(a);

	return MP_OK;
}