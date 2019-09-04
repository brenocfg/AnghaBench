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
typedef  scalar_t__ u_long ;

/* Variables and functions */

__attribute__((used)) static int set_min_max(int maxflag, u_long mib, u_long limit, u_long *oper)
{
	u_long	old ;
	old = *oper ;
	if ((limit > mib) ^ maxflag)
		*oper = limit ;
	else
		*oper = mib ;
	return old != *oper;
}