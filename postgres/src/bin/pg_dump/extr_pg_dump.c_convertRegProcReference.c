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
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 char* pg_strdup (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static char *
convertRegProcReference(Archive *fout, const char *proc)
{
	char	   *name;
	char	   *paren;
	bool		inquote;

	/* In all cases "-" means a null reference */
	if (strcmp(proc, "-") == 0)
		return NULL;

	name = pg_strdup(proc);
	/* find non-double-quoted left paren */
	inquote = false;
	for (paren = name; *paren; paren++)
	{
		if (*paren == '(' && !inquote)
		{
			*paren = '\0';
			break;
		}
		if (*paren == '"')
			inquote = !inquote;
	}
	return name;
}