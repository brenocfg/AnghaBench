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
typedef  int timelib_sll ;

/* Variables and functions */

__attribute__((used)) static timelib_sll positive_mod(timelib_sll x, timelib_sll y)
{
	timelib_sll tmp;

	tmp = x % y;
	if (tmp < 0) {
		tmp += y;
	}

	return tmp;
}