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
typedef  int zend_long ;

/* Variables and functions */

int DayOfWeek(
				 zend_long sdn)
{
	int dow;

	dow = (sdn + 1) % 7;
	if (dow >= 0) {
		return (dow);
	} else {
		return (dow + 7);
	}
}