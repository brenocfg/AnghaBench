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

bool audit_string_contains_control(const char *string, size_t len)
{
	const unsigned char *p;
	for (p = string; p < (const unsigned char *)string + len; p++) {
		if (*p == '"' || *p < 0x21 || *p > 0x7e)
			return true;
	}
	return false;
}