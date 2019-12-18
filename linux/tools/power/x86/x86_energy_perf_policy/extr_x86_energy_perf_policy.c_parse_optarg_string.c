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
 int LONG_MAX ; 
 int LONG_MIN ; 
 int OPTARG_BALANCE_PERFORMANCE ; 
 int OPTARG_BALANCE_POWER ; 
 int OPTARG_NORMAL ; 
 int OPTARG_PERFORMANCE ; 
 int OPTARG_POWER ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int parse_optarg_string(char *s)
{
	int i;
	char *endptr;

	if (!strncmp(s, "default", 7))
		return OPTARG_NORMAL;

	if (!strncmp(s, "normal", 6))
		return OPTARG_NORMAL;

	if (!strncmp(s, "power", 9))
		return OPTARG_POWER;

	if (!strncmp(s, "balance-power", 17))
		return OPTARG_BALANCE_POWER;

	if (!strncmp(s, "balance-performance", 19))
		return OPTARG_BALANCE_PERFORMANCE;

	if (!strncmp(s, "performance", 11))
		return OPTARG_PERFORMANCE;

	i = strtol(s, &endptr, 0);
	if (s == endptr) {
		fprintf(stderr, "no digits in \"%s\"\n", s);
		usage();
	}
	if (i == LONG_MIN || i == LONG_MAX)
		errx(-1, "%s", s);

	if (i > 0xFF)
		errx(-1, "%d (0x%x) must be < 256", i, i);

	if (i < 0)
		errx(-1, "%d (0x%x) must be >= 0", i, i);
	return i;
}