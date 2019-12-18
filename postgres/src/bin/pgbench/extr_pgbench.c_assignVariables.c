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
typedef  int /*<<< orphan*/  CState ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* getVariable (int /*<<< orphan*/ *,char*) ; 
 char* parseVariable (char*,int*) ; 
 char* replaceVariable (char**,char*,int,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *
assignVariables(CState *st, char *sql)
{
	char	   *p,
			   *name,
			   *val;

	p = sql;
	while ((p = strchr(p, ':')) != NULL)
	{
		int			eaten;

		name = parseVariable(p, &eaten);
		if (name == NULL)
		{
			while (*p == ':')
			{
				p++;
			}
			continue;
		}

		val = getVariable(st, name);
		free(name);
		if (val == NULL)
		{
			p++;
			continue;
		}

		p = replaceVariable(&sql, p, eaten, val);
	}

	return sql;
}