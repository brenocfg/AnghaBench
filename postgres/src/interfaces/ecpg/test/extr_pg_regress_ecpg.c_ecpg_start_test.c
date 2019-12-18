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
typedef  int /*<<< orphan*/  insource ;
typedef  int /*<<< orphan*/  inprg ;
typedef  int /*<<< orphan*/  expectfile_stdout ;
typedef  int /*<<< orphan*/  expectfile_stderr ;
typedef  int /*<<< orphan*/  expectfile_source ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  _stringlist ;
typedef  scalar_t__ PID_TYPE ;

/* Variables and functions */
 scalar_t__ INVALID_PID ; 
 int MAXPGPATH ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_stringlist_item (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  ecpg_filter (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* inputdir ; 
 char* outputdir ; 
 char* psprintf (char*,char*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  replace_string (char*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 scalar_t__ spawn_process (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static PID_TYPE
ecpg_start_test(const char *testname,
				_stringlist **resultfiles,
				_stringlist **expectfiles,
				_stringlist **tags)
{
	PID_TYPE	pid;
	char		inprg[MAXPGPATH];
	char		insource[MAXPGPATH];
	char	   *outfile_stdout,
				expectfile_stdout[MAXPGPATH];
	char	   *outfile_stderr,
				expectfile_stderr[MAXPGPATH];
	char	   *outfile_source,
				expectfile_source[MAXPGPATH];
	char		cmd[MAXPGPATH * 3];
	char	   *testname_dash;
	char	   *appnameenv;

	snprintf(inprg, sizeof(inprg), "%s/%s", inputdir, testname);

	testname_dash = strdup(testname);
	replace_string(testname_dash, "/", "-");
	snprintf(expectfile_stdout, sizeof(expectfile_stdout),
			 "%s/expected/%s.stdout",
			 outputdir, testname_dash);
	snprintf(expectfile_stderr, sizeof(expectfile_stderr),
			 "%s/expected/%s.stderr",
			 outputdir, testname_dash);
	snprintf(expectfile_source, sizeof(expectfile_source),
			 "%s/expected/%s.c",
			 outputdir, testname_dash);

	/*
	 * We can use replace_string() here because the replacement string does
	 * not occupy more space than the replaced one.
	 */
	outfile_stdout = strdup(expectfile_stdout);
	replace_string(outfile_stdout, "/expected/", "/results/");
	outfile_stderr = strdup(expectfile_stderr);
	replace_string(outfile_stderr, "/expected/", "/results/");
	outfile_source = strdup(expectfile_source);
	replace_string(outfile_source, "/expected/", "/results/");

	add_stringlist_item(resultfiles, outfile_stdout);
	add_stringlist_item(expectfiles, expectfile_stdout);
	add_stringlist_item(tags, "stdout");

	add_stringlist_item(resultfiles, outfile_stderr);
	add_stringlist_item(expectfiles, expectfile_stderr);
	add_stringlist_item(tags, "stderr");

	add_stringlist_item(resultfiles, outfile_source);
	add_stringlist_item(expectfiles, expectfile_source);
	add_stringlist_item(tags, "source");

	snprintf(insource, sizeof(insource), "%s.c", testname);
	ecpg_filter(insource, outfile_source);

	snprintf(inprg, sizeof(inprg), "%s/%s", inputdir, testname);

	snprintf(cmd, sizeof(cmd),
			 "\"%s\" >\"%s\" 2>\"%s\"",
			 inprg,
			 outfile_stdout,
			 outfile_stderr);

	appnameenv = psprintf("PGAPPNAME=ecpg/%s", testname_dash);
	putenv(appnameenv);

	pid = spawn_process(cmd);

	if (pid == INVALID_PID)
	{
		fprintf(stderr, _("could not start process for test %s\n"),
				testname);
		exit(2);
	}

	unsetenv("PGAPPNAME");
	free(appnameenv);

	free(testname_dash);
	free(outfile_stdout);
	free(outfile_stderr);
	free(outfile_source);

	return pid;
}