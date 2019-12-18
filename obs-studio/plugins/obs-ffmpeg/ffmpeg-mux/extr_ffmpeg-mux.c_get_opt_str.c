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
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static bool get_opt_str(int *p_argc, char ***p_argv, char **str,
			const char *opt)
{
	int argc = *p_argc;
	char **argv = *p_argv;

	if (!argc) {
		printf("Missing expected option: '%s'\n", opt);
		return false;
	}

	(*p_argc)--;
	(*p_argv)++;
	*str = argv[0];
	return true;
}