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
 int ALL_LOWER ; 
 int ALL_UPPER ; 
 int /*<<< orphan*/  DEBUG_elog_output ; 
 int ONE_UPPER ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char,char const,char const* const,char*) ; 
 char pg_tolower (unsigned char) ; 
 char pg_toupper (unsigned char) ; 

__attribute__((used)) static int
seq_search(char *name, const char *const *array, int type, int max, int *len)
{
	const char *p;
	const char *const *a;
	char	   *n;
	int			last,
				i;

	*len = 0;

	if (!*name)
		return -1;

	/* set first char */
	if (type == ONE_UPPER || type == ALL_UPPER)
		*name = pg_toupper((unsigned char) *name);
	else if (type == ALL_LOWER)
		*name = pg_tolower((unsigned char) *name);

	for (last = 0, a = array; *a != NULL; a++)
	{
		/* compare first chars */
		if (*name != **a)
			continue;

		for (i = 1, p = *a + 1, n = name + 1;; n++, p++, i++)
		{
			/* search fragment (max) only */
			if (max && i == max)
			{
				*len = i;
				return a - array;
			}
			/* full size */
			if (*p == '\0')
			{
				*len = i;
				return a - array;
			}
			/* Not found in array 'a' */
			if (*n == '\0')
				break;

			/*
			 * Convert (but convert new chars only)
			 */
			if (i > last)
			{
				if (type == ONE_UPPER || type == ALL_LOWER)
					*n = pg_tolower((unsigned char) *n);
				else if (type == ALL_UPPER)
					*n = pg_toupper((unsigned char) *n);
				last = i;
			}

#ifdef DEBUG_TO_FROM_CHAR
			elog(DEBUG_elog_output, "N: %c, P: %c, A: %s (%s)",
				 *n, *p, *a, name);
#endif
			if (*n != *p)
				break;
		}
	}

	return -1;
}