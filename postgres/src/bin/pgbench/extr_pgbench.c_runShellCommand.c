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
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CState ;

/* Variables and functions */
 int SHELL_COMMAND_SIZE ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* getVariable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  putVariableInt (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 scalar_t__ system (char*) ; 
 int /*<<< orphan*/  timer_exceeded ; 

__attribute__((used)) static bool
runShellCommand(CState *st, char *variable, char **argv, int argc)
{
	char		command[SHELL_COMMAND_SIZE];
	int			i,
				len = 0;
	FILE	   *fp;
	char		res[64];
	char	   *endptr;
	int			retval;

	/*----------
	 * Join arguments with whitespace separators. Arguments starting with
	 * exactly one colon are treated as variables:
	 *	name - append a string "name"
	 *	:var - append a variable named 'var'
	 *	::name - append a string ":name"
	 *----------
	 */
	for (i = 0; i < argc; i++)
	{
		char	   *arg;
		int			arglen;

		if (argv[i][0] != ':')
		{
			arg = argv[i];		/* a string literal */
		}
		else if (argv[i][1] == ':')
		{
			arg = argv[i] + 1;	/* a string literal starting with colons */
		}
		else if ((arg = getVariable(st, argv[i] + 1)) == NULL)
		{
			fprintf(stderr, "%s: undefined variable \"%s\"\n",
					argv[0], argv[i]);
			return false;
		}

		arglen = strlen(arg);
		if (len + arglen + (i > 0 ? 1 : 0) >= SHELL_COMMAND_SIZE - 1)
		{
			fprintf(stderr, "%s: shell command is too long\n", argv[0]);
			return false;
		}

		if (i > 0)
			command[len++] = ' ';
		memcpy(command + len, arg, arglen);
		len += arglen;
	}

	command[len] = '\0';

	/* Fast path for non-assignment case */
	if (variable == NULL)
	{
		if (system(command))
		{
			if (!timer_exceeded)
				fprintf(stderr, "%s: could not launch shell command\n", argv[0]);
			return false;
		}
		return true;
	}

	/* Execute the command with pipe and read the standard output. */
	if ((fp = popen(command, "r")) == NULL)
	{
		fprintf(stderr, "%s: could not launch shell command\n", argv[0]);
		return false;
	}
	if (fgets(res, sizeof(res), fp) == NULL)
	{
		if (!timer_exceeded)
			fprintf(stderr, "%s: could not read result of shell command\n", argv[0]);
		(void) pclose(fp);
		return false;
	}
	if (pclose(fp) < 0)
	{
		fprintf(stderr, "%s: could not close shell command\n", argv[0]);
		return false;
	}

	/* Check whether the result is an integer and assign it to the variable */
	retval = (int) strtol(res, &endptr, 10);
	while (*endptr != '\0' && isspace((unsigned char) *endptr))
		endptr++;
	if (*res == '\0' || *endptr != '\0')
	{
		fprintf(stderr, "%s: shell command must return an integer (not \"%s\")\n",
				argv[0], res);
		return false;
	}
	if (!putVariableInt(st, "setshell", variable, retval))
		return false;

#ifdef DEBUG
	printf("shell parameter name: \"%s\", value: \"%s\"\n", argv[1], res);
#endif
	return true;
}