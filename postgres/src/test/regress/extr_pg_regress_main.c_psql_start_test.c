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
 char* _ (char*) ; 
 int /*<<< orphan*/  add_stringlist_item (int /*<<< orphan*/ **,char*) ; 
 char* bindir ; 
 TYPE_1__* dblist ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file_exists (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* inputdir ; 
 char* launcher ; 
 char* outputdir ; 
 char* psprintf (char*,char const*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 scalar_t__ snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ spawn_process (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static PID_TYPE
psql_start_test(const char *testname,
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

	/*
	 * Look for files in the output dir first, consistent with a vpath search.
	 * This is mainly to create more reasonable error messages if the file is
	 * not found.  It also allows local test overrides when running pg_regress
	 * outside of the source tree.
	 */
	snprintf(infile, sizeof(infile), "%s/sql/%s.sql",
			 outputdir, testname);
	if (!file_exists(infile))
		snprintf(infile, sizeof(infile), "%s/sql/%s.sql",
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

	/*
	 * Use HIDE_TABLEAM to hide different AMs to allow to use regression tests
	 * against different AMs without unnecessary differences.
	 */
	offset += snprintf(psql_cmd + offset, sizeof(psql_cmd) - offset,
					   "\"%s%spsql\" -X -a -q -d \"%s\" -v %s < \"%s\" > \"%s\" 2>&1",
					   bindir ? bindir : "",
					   bindir ? "/" : "",
					   dblist->str,
					   "HIDE_TABLEAM=\"on\"",
					   infile,
					   outfile);
	if (offset >= sizeof(psql_cmd))
	{
		fprintf(stderr, _("command too long\n"));
		exit(2);
	}

	appnameenv = psprintf("PGAPPNAME=pg_regress/%s", testname);
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