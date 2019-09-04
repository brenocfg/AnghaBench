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

__attribute__((used)) static void test_ubsan_load_invalid_value(void)
{
	volatile char *dst, *src;
	bool val, val2, *ptr;
	char c = 4;

	dst = (char *)&val;
	src = &c;
	*dst = *src;

	ptr = &val2;
	val2 = val;
}