#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  relpath ;
struct TYPE_2__ {char* inputfile; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int MAXPGPATH ; 
 int MainLoop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int /*<<< orphan*/  PG_LOG_FLAG_TERSE ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_parent_directory (char*) ; 
 int /*<<< orphan*/  has_drive_prefix (char*) ; 
 int /*<<< orphan*/  is_absolute_path (char*) ; 
 int /*<<< orphan*/  join_path_components (char*,char*,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int /*<<< orphan*/  pg_logging_config (int /*<<< orphan*/ ) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

int
process_file(char *filename, bool use_relative_path)
{
	FILE	   *fd;
	int			result;
	char	   *oldfilename;
	char		relpath[MAXPGPATH];

	if (!filename)
	{
		fd = stdin;
		filename = NULL;
	}
	else if (strcmp(filename, "-") != 0)
	{
		canonicalize_path(filename);

		/*
		 * If we were asked to resolve the pathname relative to the location
		 * of the currently executing script, and there is one, and this is a
		 * relative pathname, then prepend all but the last pathname component
		 * of the current script to this pathname.
		 */
		if (use_relative_path && pset.inputfile &&
			!is_absolute_path(filename) && !has_drive_prefix(filename))
		{
			strlcpy(relpath, pset.inputfile, sizeof(relpath));
			get_parent_directory(relpath);
			join_path_components(relpath, relpath, filename);
			canonicalize_path(relpath);

			filename = relpath;
		}

		fd = fopen(filename, PG_BINARY_R);

		if (!fd)
		{
			pg_log_error("%s: %m", filename);
			return EXIT_FAILURE;
		}
	}
	else
	{
		fd = stdin;
		filename = "<stdin>";	/* for future error messages */
	}

	oldfilename = pset.inputfile;
	pset.inputfile = filename;

	pg_logging_config(pset.inputfile ? 0 : PG_LOG_FLAG_TERSE);

	result = MainLoop(fd);

	if (fd != stdin)
		fclose(fd);

	pset.inputfile = oldfilename;

	pg_logging_config(pset.inputfile ? 0 : PG_LOG_FLAG_TERSE);

	return result;
}