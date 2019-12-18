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

__attribute__((used)) static bool
is_separator_char(const char *str)
{
	/* ASCII printable character, but not letter or digit */
	return (*str > 0x20 && *str < 0x7F &&
			!(*str >= 'A' && *str <= 'Z') &&
			!(*str >= 'a' && *str <= 'z') &&
			!(*str >= '0' && *str <= '9'));
}