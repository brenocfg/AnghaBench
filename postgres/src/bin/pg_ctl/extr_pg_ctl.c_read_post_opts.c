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
 scalar_t__ RESTART_COMMAND ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ ctl_command ; 
 int /*<<< orphan*/ * exec_path ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free_readfile (char**) ; 
 void* pg_strdup (char*) ; 
 char* post_opts ; 
 int /*<<< orphan*/  postopts_file ; 
 int /*<<< orphan*/  progname ; 
 char** readfile (int /*<<< orphan*/ ,int*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_post_opts(void)
{
	if (post_opts == NULL)
	{
		post_opts = "";			/* default */
		if (ctl_command == RESTART_COMMAND)
		{
			char	  **optlines;
			int			numlines;

			optlines = readfile(postopts_file, &numlines);
			if (optlines == NULL)
			{
				write_stderr(_("%s: could not read file \"%s\"\n"), progname, postopts_file);
				exit(1);
			}
			else if (numlines != 1)
			{
				write_stderr(_("%s: option file \"%s\" must have exactly one line\n"),
							 progname, postopts_file);
				exit(1);
			}
			else
			{
				char	   *optline;
				char	   *arg1;

				optline = optlines[0];

				/*
				 * Are we at the first option, as defined by space and
				 * double-quote?
				 */
				if ((arg1 = strstr(optline, " \"")) != NULL)
				{
					*arg1 = '\0';	/* terminate so we get only program name */
					post_opts = pg_strdup(arg1 + 1);	/* point past whitespace */
				}
				if (exec_path == NULL)
					exec_path = pg_strdup(optline);
			}

			/* Free the results of readfile. */
			free_readfile(optlines);
		}
	}
}