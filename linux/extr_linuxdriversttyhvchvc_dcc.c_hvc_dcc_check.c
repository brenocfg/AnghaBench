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
 int DCC_STATUS_TX ; 
 int HZ ; 
 int __dcc_getstatus () ; 
 int /*<<< orphan*/  __dcc_putchar (char) ; 
 int jiffies ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 

__attribute__((used)) static bool hvc_dcc_check(void)
{
	unsigned long time = jiffies + (HZ / 10);

	/* Write a test character to check if it is handled */
	__dcc_putchar('\n');

	while (time_is_after_jiffies(time)) {
		if (!(__dcc_getstatus() & DCC_STATUS_TX))
			return true;
	}

	return false;
}