#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mp_int ;
struct TYPE_5__ {scalar_t__* digits; } ;

/* Variables and functions */
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int MP_USED (TYPE_1__*) ; 
 scalar_t__ MP_ZPOS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
mp_int_compare_zero(mp_int z)
{
	assert(z != NULL);

	if (MP_USED(z) == 1 && z->digits[0] == 0)
	{
		return 0;
	}
	else if (MP_SIGN(z) == MP_ZPOS)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}