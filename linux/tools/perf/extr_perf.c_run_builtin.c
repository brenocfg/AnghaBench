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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct cmd_struct {int option; int (* fn ) (int,char const**) ;int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int RUN_SETUP ; 
 int STRERR_BUFSIZE ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int USE_PAGER ; 
 int /*<<< orphan*/  bpf__clear () ; 
 int check_browser_config (int /*<<< orphan*/ ) ; 
 int check_pager_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit_browser (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  perf_config__exit () ; 
 int /*<<< orphan*/  perf_env ; 
 int /*<<< orphan*/  perf_env__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_env__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_env__set_cmdline (int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* str_error_r (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (int,char const**) ; 
 int use_browser ; 
 int use_pager ; 

__attribute__((used)) static int run_builtin(struct cmd_struct *p, int argc, const char **argv)
{
	int status;
	struct stat st;
	char sbuf[STRERR_BUFSIZE];

	if (use_browser == -1)
		use_browser = check_browser_config(p->cmd);

	if (use_pager == -1 && p->option & RUN_SETUP)
		use_pager = check_pager_config(p->cmd);
	if (use_pager == -1 && p->option & USE_PAGER)
		use_pager = 1;
	commit_pager_choice();

	perf_env__init(&perf_env);
	perf_env__set_cmdline(&perf_env, argc, argv);
	status = p->fn(argc, argv);
	perf_config__exit();
	exit_browser(status);
	perf_env__exit(&perf_env);
	bpf__clear();

	if (status)
		return status & 0xff;

	/* Somebody closed stdout? */
	if (fstat(fileno(stdout), &st))
		return 0;
	/* Ignore write errors for pipes and sockets.. */
	if (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))
		return 0;

	status = 1;
	/* Check for ENOSPC and EIO errors.. */
	if (fflush(stdout)) {
		fprintf(stderr, "write failure on standard output: %s",
			str_error_r(errno, sbuf, sizeof(sbuf)));
		goto out;
	}
	if (ferror(stdout)) {
		fprintf(stderr, "unknown write failure on standard output");
		goto out;
	}
	if (fclose(stdout)) {
		fprintf(stderr, "close failed on standard output: %s",
			str_error_r(errno, sbuf, sizeof(sbuf)));
		goto out;
	}
	status = 0;
out:
	return status;
}