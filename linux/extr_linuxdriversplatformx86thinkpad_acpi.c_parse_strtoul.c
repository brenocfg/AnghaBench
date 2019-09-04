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
 int EINVAL ; 
 unsigned long simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 char* skip_spaces (char const*) ; 

__attribute__((used)) static int parse_strtoul(const char *buf,
		unsigned long max, unsigned long *value)
{
	char *endp;

	*value = simple_strtoul(skip_spaces(buf), &endp, 0);
	endp = skip_spaces(endp);
	if (*endp || *value > max)
		return -EINVAL;

	return 0;
}