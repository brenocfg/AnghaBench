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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *
get_alternative_expectfile(const char *expectfile, int i)
{
	char	   *last_dot;
	int			ssize = strlen(expectfile) + 2 + 1;
	char	   *tmp;
	char	   *s;

	if (!(tmp = (char *) malloc(ssize)))
		return NULL;

	if (!(s = (char *) malloc(ssize)))
	{
		free(tmp);
		return NULL;
	}

	strcpy(tmp, expectfile);
	last_dot = strrchr(tmp, '.');
	if (!last_dot)
	{
		free(tmp);
		free(s);
		return NULL;
	}
	*last_dot = '\0';
	snprintf(s, ssize, "%s_%d.%s", tmp, i, last_dot + 1);
	free(tmp);
	return s;
}