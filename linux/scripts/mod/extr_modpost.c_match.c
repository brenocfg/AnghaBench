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
 char* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  strndup (char const*,int) ; 
 scalar_t__ strrcmp (char const*,char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int match(const char *sym, const char * const pat[])
{
	const char *p;
	while (*pat) {
		p = *pat++;
		const char *endp = p + strlen(p) - 1;

		/* "*foo*" */
		if (*p == '*' && *endp == '*') {
			char *bare = NOFAIL(strndup(p + 1, strlen(p) - 2));
			char *here = strstr(sym, bare);

			free(bare);
			if (here != NULL)
				return 1;
		}
		/* "*foo" */
		else if (*p == '*') {
			if (strrcmp(sym, p + 1) == 0)
				return 1;
		}
		/* "foo*" */
		else if (*endp == '*') {
			if (strncmp(sym, p, strlen(p) - 1) == 0)
				return 1;
		}
		/* no wildcards */
		else {
			if (strcmp(p, sym) == 0)
				return 1;
		}
	}
	/* no match */
	return 0;
}