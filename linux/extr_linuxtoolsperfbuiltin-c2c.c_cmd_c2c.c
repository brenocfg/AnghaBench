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
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int /*<<< orphan*/  c2c_options ; 
 int /*<<< orphan*/  c2c_usage ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_c2c__record (int,char const**) ; 
 int perf_c2c__report (int,char const**) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cmd_c2c(int argc, const char **argv)
{
	argc = parse_options(argc, argv, c2c_options, c2c_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	if (!argc)
		usage_with_options(c2c_usage, c2c_options);

	if (!strncmp(argv[0], "rec", 3)) {
		return perf_c2c__record(argc, argv);
	} else if (!strncmp(argv[0], "rep", 3)) {
		return perf_c2c__report(argc, argv);
	} else {
		usage_with_options(c2c_usage, c2c_options);
	}

	return 0;
}