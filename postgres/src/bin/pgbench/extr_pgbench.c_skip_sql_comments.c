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
 scalar_t__ isspace (unsigned char) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
skip_sql_comments(char *sql_command)
{
	char	   *p = sql_command;

	/* Skip any leading whitespace, as well as "--" style comments */
	for (;;)
	{
		if (isspace((unsigned char) *p))
			p++;
		else if (strncmp(p, "--", 2) == 0)
		{
			p = strchr(p, '\n');
			if (p == NULL)
				return NULL;
			p++;
		}
		else
			break;
	}

	/* NULL if there's nothing but whitespace and comments */
	if (*p == '\0')
		return NULL;

	return p;
}