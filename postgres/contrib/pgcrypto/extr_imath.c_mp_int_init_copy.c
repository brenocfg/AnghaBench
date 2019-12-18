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
typedef  int mp_size ;
typedef  scalar_t__ mp_result ;
typedef  TYPE_1__* mp_int ;
struct TYPE_8__ {int used; int /*<<< orphan*/  sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_DIGITS (TYPE_1__*) ; 
 scalar_t__ MP_OK ; 
 int MP_USED (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  default_precision ; 
 int /*<<< orphan*/  mp_int_init (TYPE_1__*) ; 
 scalar_t__ mp_int_init_size (TYPE_1__*,int) ; 

mp_result
mp_int_init_copy(mp_int z, mp_int old)
{
	assert(z != NULL && old != NULL);

	mp_size		uold = MP_USED(old);

	if (uold == 1)
	{
		mp_int_init(z);
	}
	else
	{
		mp_size		target = MAX(uold, default_precision);
		mp_result	res = mp_int_init_size(z, target);

		if (res != MP_OK)
			return res;
	}

	z->used = uold;
	z->sign = old->sign;
	COPY(MP_DIGITS(old), MP_DIGITS(z), uold);

	return MP_OK;
}