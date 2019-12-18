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
 char* get_user_name (char**) ; 
 int geteuid () ; 
 int /*<<< orphan*/  pg_fatal (char*,char*) ; 
 char* pg_strdup (char const*) ; 

int
get_user_info(char **user_name_p)
{
	int			user_id;
	const char *user_name;
	char	   *errstr;

#ifndef WIN32
	user_id = geteuid();
#else
	user_id = 1;
#endif

	user_name = get_user_name(&errstr);
	if (!user_name)
		pg_fatal("%s\n", errstr);

	/* make a copy */
	*user_name_p = pg_strdup(user_name);

	return user_id;
}