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

/* Variables and functions */
 size_t __arraycount (int*) ; 
 scalar_t__ isleap (int) ; 
 int* mdays ; 

__attribute__((used)) static int
cdf_getday(int year, int days)
{
	size_t m;

	for (m = 0; m < __arraycount(mdays); m++) {
		int sub = mdays[m] + (m == 1 && isleap(year));
		if (days < sub)
			return days;
		days -= sub;
	}
	return days;
}