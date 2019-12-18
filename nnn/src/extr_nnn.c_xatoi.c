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
typedef  int uint ;

/* Variables and functions */
 scalar_t__ xisdigit (char const) ; 

__attribute__((used)) static uint xatoi(const char *str)
{
	int val = 0;

	if (!str)
		return 0;

	while (xisdigit(*str)) {
		val = val * 10 + (*str - '0');
		++str;
	}

	return val;
}