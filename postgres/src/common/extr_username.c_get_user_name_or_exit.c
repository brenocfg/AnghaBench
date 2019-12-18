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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* get_user_name (char**) ; 
 int /*<<< orphan*/  stderr ; 

const char *
get_user_name_or_exit(const char *progname)
{
	const char *user_name;
	char	   *errstr;

	user_name = get_user_name(&errstr);

	if (!user_name)
	{
		fprintf(stderr, "%s: %s\n", progname, errstr);
		exit(1);
	}
	return user_name;
}