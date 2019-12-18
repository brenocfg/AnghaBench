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
 int atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* getVariable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pg_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool
evaluateSleep(CState *st, int argc, char **argv, int *usecs)
{
	char	   *var;
	int			usec;

	if (*argv[1] == ':')
	{
		if ((var = getVariable(st, argv[1] + 1)) == NULL)
		{
			fprintf(stderr, "%s: undefined variable \"%s\"\n",
					argv[0], argv[1]);
			return false;
		}
		usec = atoi(var);
	}
	else
		usec = atoi(argv[1]);

	if (argc > 2)
	{
		if (pg_strcasecmp(argv[2], "ms") == 0)
			usec *= 1000;
		else if (pg_strcasecmp(argv[2], "s") == 0)
			usec *= 1000000;
	}
	else
		usec *= 1000000;

	*usecs = usec;
	return true;
}