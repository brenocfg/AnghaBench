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

__attribute__((used)) static int
adjust_sign(int is_negative, int forcesign, int *signvalue)
{
	if (is_negative)
	{
		*signvalue = '-';
		return true;
	}
	else if (forcesign)
		*signvalue = '+';
	return false;
}