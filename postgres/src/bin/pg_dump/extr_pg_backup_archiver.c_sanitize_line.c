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
 char* pg_strdup (char const*) ; 

__attribute__((used)) static char *
sanitize_line(const char *str, bool want_hyphen)
{
	char	   *result;
	char	   *s;

	if (!str)
		return pg_strdup(want_hyphen ? "-" : "");

	result = pg_strdup(str);

	for (s = result; *s != '\0'; s++)
	{
		if (*s == '\n' || *s == '\r')
			*s = ' ';
	}

	return result;
}