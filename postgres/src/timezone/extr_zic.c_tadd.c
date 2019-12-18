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
typedef  scalar_t__ zic_t ;

/* Variables and functions */
 scalar_t__ max_time ; 
 scalar_t__ min_time ; 
 int /*<<< orphan*/  time_overflow () ; 

__attribute__((used)) static zic_t
tadd(zic_t t1, zic_t t2)
{
	if (t1 < 0)
	{
		if (t2 < min_time - t1)
		{
			if (t1 != min_time)
				time_overflow();
			return min_time;
		}
	}
	else
	{
		if (max_time - t1 < t2)
		{
			if (t1 != max_time)
				time_overflow();
			return max_time;
		}
	}
	return t1 + t2;
}