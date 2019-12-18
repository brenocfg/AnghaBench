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
typedef  int /*<<< orphan*/  psql_cmd ;
typedef  int /*<<< orphan*/  outfile ;
typedef  int /*<<< orphan*/  infile ;
typedef  int /*<<< orphan*/  expectfile ;
typedef  int /*<<< orphan*/  _stringlist ;
struct TYPE_2__ {char* str; } ;
typedef  scalar_t__ PID_TYPE ;

/* Variables and functions */
 scalar_t__ INVALID_PID ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_ISOLATION_VERSIONSTR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_stringlist_item (int /*<<< orphan*/ **,char*) ; 
 TYPE_1__* dblist ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file_exists (char*) ; 
 scalar_t__ find_other_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* inputdir ; 
 char* isolation_exec ; 
 char* launcher ; 
 int looked_up_isolation_exec ; 
 char* outputdir ; 
 char* psprintf (char*,char const*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  saved_argv0 ; 
 scalar_t__ snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ spawn_process (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static PID_TYPE
isolation_start_test(const char *testname,
					 _stringlist **resultfiles,
					 _stringlist **expectfiles,
					 _stringlist **tags)
{
	PID_TYPE	pid;
	char		infile[MAXPGPATH];
	char		outfile[MAXPGPATH];
	char		expectfile[MAXPGPATH];
	char		psql_cmd[MAXPGPATH * 3];
	size_t		offset = 0;
	char	   *appnameenv;

	/* need to do the path lookup here, check isolation_init() for details */
	if (!looked_up_isolation_exec)
	{
		/* look for isolationtester binary */
		if (find_other_exec(saved_argv0, "isolationtester",
							PG_ISOLATION_VERSIONSTR, isolation_exec) != 0)
		{
			fprintf(stderr, _("could not find proper isolationtester binary\n"));
			exit(2);
		}
		looked_up_isolation_exec = true;
	}

	/*
	 * Look for files in the output dir first, consistent with a vpath search.
	 * This is mainly to create more reasonable error messages if the file is
	 * not found.  It also allows local test overrides when running pg_regress
	 * outside of the source tree.
	 */
	snprintf(infile, sizeof(infile), "%s/specs/%s.spec",
			 outputdir, testname);
	if (!file_exists(infile))
		snprintf(infile, sizeof(infile), "%s/specs/%s.spec",
				 inputdir, testname);

	snprintf(outfile, sizeof(outfile), "%s/results/%s.out",
			 outputdir, testname);

	snprintf(expectfile, sizeof(expectfile), "%s/expected/%s.out",
			 outputdir, testname);
	if (!file_exists(expectfile))
		snprintf(expectfile, sizeof(expectfile), "%s/expected/%s.out",
				 inputdir, testname);

	add_stringlist_item(resultfiles, outfile);
	add_stringlist_item(expectfiles, expectfile);

	if (launcher)
	{
		offset += snprintf(psql_cmd + offset, sizeof(psql_cmd) - offset,
						   "%s ", launcher);
		if (offset >= sizeof(psql_cmd))
		{
			fprintf(stderr, _("command too long\n"));
			exit(2);
		}
	}

	offset += snprintf(psql_cmd + offset, sizeof(psql_cmd) - offset,
					   "\"%s\" \"dbname=%s\" < \"%s\" > \"%s\" 2>&1",
					   isolation_exec,
					   dblist->str,
					   infile,
					   outfile);
	if (offset >= sizeof(psql_cmd))
	{
		fprintf(stderr, _("command too long\n"));
		exit(2);
	}

	appnameenv = psprintf("PGAPPNAME=isolation/%s", testname);
	putenv(appnameenv);

	pid = spawn_process(psql_cmd);

	if (pid == INVALID_PID)
	{
		fprintf(stderr, _("could not start process for test %s\n"),
				testname);
		exit(2);
	}

	unsetenv("PGAPPNAME");
	free(appnameenv);

	return pid;
}