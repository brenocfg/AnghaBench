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
 char*** _NSGetArgv () ; 
 char** environ ; 
 int /*<<< orphan*/  exit (int) ; 
 int last_status_len ; 
 scalar_t__ malloc (int) ; 
 char* ps_buffer ; 
 int ps_buffer_size ; 
 int save_argc ; 
 char** save_argv ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  write_stderr (char*) ; 

char	  **
save_ps_display_args(int argc, char **argv)
{
	save_argc = argc;
	save_argv = argv;

#if defined(PS_USE_CLOBBER_ARGV)

	/*
	 * If we're going to overwrite the argv area, count the available space.
	 * Also move the environment to make additional room.
	 */
	{
		char	   *end_of_area = NULL;
		char	  **new_environ;
		int			i;

		/*
		 * check for contiguous argv strings
		 */
		for (i = 0; i < argc; i++)
		{
			if (i == 0 || end_of_area + 1 == argv[i])
				end_of_area = argv[i] + strlen(argv[i]);
		}

		if (end_of_area == NULL)	/* probably can't happen? */
		{
			ps_buffer = NULL;
			ps_buffer_size = 0;
			return argv;
		}

		/*
		 * check for contiguous environ strings following argv
		 */
		for (i = 0; environ[i] != NULL; i++)
		{
			if (end_of_area + 1 == environ[i])
				end_of_area = environ[i] + strlen(environ[i]);
		}

		ps_buffer = argv[0];
		last_status_len = ps_buffer_size = end_of_area - argv[0];

		/*
		 * move the environment out of the way
		 */
		new_environ = (char **) malloc((i + 1) * sizeof(char *));
		if (!new_environ)
		{
			write_stderr("out of memory\n");
			exit(1);
		}
		for (i = 0; environ[i] != NULL; i++)
		{
			new_environ[i] = strdup(environ[i]);
			if (!new_environ[i])
			{
				write_stderr("out of memory\n");
				exit(1);
			}
		}
		new_environ[i] = NULL;
		environ = new_environ;
	}
#endif							/* PS_USE_CLOBBER_ARGV */

#if defined(PS_USE_CHANGE_ARGV) || defined(PS_USE_CLOBBER_ARGV)

	/*
	 * If we're going to change the original argv[] then make a copy for
	 * argument parsing purposes.
	 *
	 * (NB: do NOT think to remove the copying of argv[], even though
	 * postmaster.c finishes looking at argv[] long before we ever consider
	 * changing the ps display.  On some platforms, getopt() keeps pointers
	 * into the argv array, and will get horribly confused when it is
	 * re-called to analyze a subprocess' argument string if the argv storage
	 * has been clobbered meanwhile.  Other platforms have other dependencies
	 * on argv[].
	 */
	{
		char	  **new_argv;
		int			i;

		new_argv = (char **) malloc((argc + 1) * sizeof(char *));
		if (!new_argv)
		{
			write_stderr("out of memory\n");
			exit(1);
		}
		for (i = 0; i < argc; i++)
		{
			new_argv[i] = strdup(argv[i]);
			if (!new_argv[i])
			{
				write_stderr("out of memory\n");
				exit(1);
			}
		}
		new_argv[argc] = NULL;

#if defined(__darwin__)

		/*
		 * macOS (and perhaps other NeXT-derived platforms?) has a static copy
		 * of the argv pointer, which we may fix like so:
		 */
		*_NSGetArgv() = new_argv;
#endif

		argv = new_argv;
	}
#endif							/* PS_USE_CHANGE_ARGV or PS_USE_CLOBBER_ARGV */

	return argv;
}