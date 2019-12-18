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
typedef  int /*<<< orphan*/  file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPGPATH ; 
 char* _ (char*) ; 
 char* difffilename ; 
 int /*<<< orphan*/  directory_exists (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 void* logfile ; 
 char* logfilename ; 
 int /*<<< orphan*/  make_directory (char*) ; 
 char* outputdir ; 
 char* pg_strdup (char*) ; 
 char* progname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_result_files(void)
{
	char		file[MAXPGPATH];
	FILE	   *difffile;

	/* create outputdir directory if not present */
	if (!directory_exists(outputdir))
		make_directory(outputdir);

	/* create the log file (copy of running status output) */
	snprintf(file, sizeof(file), "%s/regression.out", outputdir);
	logfilename = pg_strdup(file);
	logfile = fopen(logfilename, "w");
	if (!logfile)
	{
		fprintf(stderr, _("%s: could not open file \"%s\" for writing: %s\n"),
				progname, logfilename, strerror(errno));
		exit(2);
	}

	/* create the diffs file as empty */
	snprintf(file, sizeof(file), "%s/regression.diffs", outputdir);
	difffilename = pg_strdup(file);
	difffile = fopen(difffilename, "w");
	if (!difffile)
	{
		fprintf(stderr, _("%s: could not open file \"%s\" for writing: %s\n"),
				progname, difffilename, strerror(errno));
		exit(2);
	}
	/* we don't keep the diffs file open continuously */
	fclose(difffile);

	/* also create the results directory if not present */
	snprintf(file, sizeof(file), "%s/results", outputdir);
	if (!directory_exists(file))
		make_directory(file);
}