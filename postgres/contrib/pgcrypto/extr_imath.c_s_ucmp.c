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
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DIGITS (int /*<<< orphan*/ ) ; 
 scalar_t__ MP_USED (int /*<<< orphan*/ ) ; 
 int s_cdig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
s_ucmp(mp_int a, mp_int b)
{
	mp_size		ua = MP_USED(a),
				ub = MP_USED(b);

	if (ua > ub)
	{
		return 1;
	}
	else if (ub > ua)
	{
		return -1;
	}
	else
	{
		return s_cdig(MP_DIGITS(a), MP_DIGITS(b), ua);
	}
}