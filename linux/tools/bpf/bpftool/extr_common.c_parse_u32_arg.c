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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT_ARGP () ; 
 int /*<<< orphan*/  p_err (char*,char const*,...) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int /*<<< orphan*/ ) ; 

int parse_u32_arg(int *argc, char ***argv, __u32 *val, const char *what)
{
	char *endptr;

	NEXT_ARGP();

	if (*val) {
		p_err("%s already specified", what);
		return -1;
	}

	*val = strtoul(**argv, &endptr, 0);
	if (*endptr) {
		p_err("can't parse %s as %s", **argv, what);
		return -1;
	}
	NEXT_ARGP();

	return 0;
}