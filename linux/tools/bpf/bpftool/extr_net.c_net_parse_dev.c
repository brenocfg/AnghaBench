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
 int /*<<< orphan*/  NEXT_ARGP () ; 
 int if_nametoindex (char*) ; 
 scalar_t__ is_prefix (char*,char*) ; 
 int /*<<< orphan*/  p_err (char*,char*) ; 

__attribute__((used)) static int net_parse_dev(int *argc, char ***argv)
{
	int ifindex;

	if (is_prefix(**argv, "dev")) {
		NEXT_ARGP();

		ifindex = if_nametoindex(**argv);
		if (!ifindex)
			p_err("invalid devname %s", **argv);

		NEXT_ARGP();
	} else {
		p_err("expected 'dev', got: '%s'?", **argv);
		return -1;
	}

	return ifindex;
}