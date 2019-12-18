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
 int /*<<< orphan*/  free (char**) ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  memcpy (char**,char const**,int) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  record_options ; 
 int system_wide ; 

__attribute__((used)) static int have_cmd(int argc, const char **argv)
{
	char **__argv = malloc(sizeof(const char *) * argc);

	if (!__argv) {
		pr_err("malloc failed\n");
		return -1;
	}

	memcpy(__argv, argv, sizeof(const char *) * argc);
	argc = parse_options(argc, (const char **)__argv, record_options,
			     NULL, PARSE_OPT_STOP_AT_NON_OPTION);
	free(__argv);

	system_wide = (argc == 0);

	return 0;
}