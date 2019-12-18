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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char** emalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ is_space (char) ; 
 int /*<<< orphan*/  size_product (scalar_t__,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char **
getfields(char *cp)
{
	char	   *dp;
	char	  **array;
	int			nsubs;

	if (cp == NULL)
		return NULL;
	array = emalloc(size_product(strlen(cp) + 1, sizeof *array));
	nsubs = 0;
	for (;;)
	{
		while (is_space(*cp))
			++cp;
		if (*cp == '\0' || *cp == '#')
			break;
		array[nsubs++] = dp = cp;
		do
		{
			if ((*dp = *cp++) != '"')
				++dp;
			else
				while ((*dp = *cp++) != '"')
					if (*dp != '\0')
						++dp;
					else
					{
						error(_("Odd number of quotation marks"));
						exit(EXIT_FAILURE);
					}
		} while (*cp && *cp != '#' && !is_space(*cp));
		if (is_space(*cp))
			++cp;
		*dp = '\0';
	}
	array[nsubs] = NULL;
	return array;
}