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
 unsigned long UINT_MAX ; 
 scalar_t__ errno ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_num(unsigned *num, const char *str)
{
	unsigned long val;
	char *end;

	errno = 0;
	val = strtoul(str, &end, 0);
	if (errno || *end || val > UINT_MAX)
		return -1;
	*num = val;
	return 0;
}