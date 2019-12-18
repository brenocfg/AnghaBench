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
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 scalar_t__ MP_OK ; 
 scalar_t__ mp_int_div_value (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

bool
mp_int_divisible_value(mp_int a, mp_small v)
{
	mp_small	rem = 0;

	if (mp_int_div_value(a, v, NULL, &rem) != MP_OK)
	{
		return false;
	}
	return rem == 0;
}