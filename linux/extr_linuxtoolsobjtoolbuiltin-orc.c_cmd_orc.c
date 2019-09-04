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
 int check (char const*,int) ; 
 int /*<<< orphan*/  check_options ; 
 int orc_dump (char const*) ; 
 int /*<<< orphan*/  orc_usage ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cmd_orc(int argc, const char **argv)
{
	const char *objname;

	argc--; argv++;
	if (argc <= 0)
		usage_with_options(orc_usage, check_options);

	if (!strncmp(argv[0], "gen", 3)) {
		argc = parse_options(argc, argv, check_options, orc_usage, 0);
		if (argc != 1)
			usage_with_options(orc_usage, check_options);

		objname = argv[0];

		return check(objname, true);
	}

	if (!strcmp(argv[0], "dump")) {
		if (argc != 2)
			usage_with_options(orc_usage, check_options);

		objname = argv[1];

		return orc_dump(objname);
	}

	usage_with_options(orc_usage, check_options);

	return 0;
}