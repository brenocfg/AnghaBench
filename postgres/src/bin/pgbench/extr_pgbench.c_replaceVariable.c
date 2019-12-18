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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* pg_realloc (char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
replaceVariable(char **sql, char *param, int len, char *value)
{
	int			valueln = strlen(value);

	if (valueln > len)
	{
		size_t		offset = param - *sql;

		*sql = pg_realloc(*sql, strlen(*sql) - len + valueln + 1);
		param = *sql + offset;
	}

	if (valueln != len)
		memmove(param + valueln, param + len, strlen(param + len) + 1);
	memcpy(param, value, valueln);

	return param + valueln;
}