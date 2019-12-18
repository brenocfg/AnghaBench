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

__attribute__((used)) static int from_bcd(int bcdnum)
{
	int fac, num = 0;

	for (fac = 1; bcdnum; fac *= 10) {
		num += (bcdnum % 16) * fac;
		bcdnum /= 16;
	}

	return num;
}