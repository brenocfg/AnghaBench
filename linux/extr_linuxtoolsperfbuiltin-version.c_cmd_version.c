#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ build_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_OPT_STOP_AT_NON_OPTION ; 
 int /*<<< orphan*/  library_status () ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* perf_version_string ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_1__ version ; 
 int /*<<< orphan*/  version_options ; 
 int /*<<< orphan*/  version_usage ; 
 int version_verbose ; 

int cmd_version(int argc, const char **argv)
{
	argc = parse_options(argc, argv, version_options, version_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	printf("perf version %s\n", perf_version_string);

	if (version.build_options || version_verbose == 1)
		library_status();

	return 0;
}