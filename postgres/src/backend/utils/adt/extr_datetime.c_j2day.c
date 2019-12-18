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

int
j2day(int date)
{
	date += 1;
	date %= 7;
	/* Cope if division truncates towards zero, as it probably does */
	if (date < 0)
		date += 7;

	return date;
}