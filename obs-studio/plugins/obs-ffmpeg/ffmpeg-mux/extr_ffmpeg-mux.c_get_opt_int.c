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
 int atoi (char*) ; 
 int /*<<< orphan*/  get_opt_str (int*,char***,char**,char const*) ; 

__attribute__((used)) static bool get_opt_int(int *p_argc, char ***p_argv, int *i, const char *opt)
{
	char *str;

	if (!get_opt_str(p_argc, p_argv, &str, opt)) {
		return false;
	}

	*i = atoi(str);
	return true;
}