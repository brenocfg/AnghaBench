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
 int /*<<< orphan*/  ENOENT ; 
 int ERR_RUN_COMMAND_EXEC ; 
 scalar_t__ IS_RUN_COMMAND_ERR (int) ; 
 scalar_t__ asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static void execv_dashed_external(const char **argv)
{
	char *cmd;
	const char *tmp;
	int status;

	if (asprintf(&cmd, "perf-%s", argv[0]) < 0)
		goto do_die;

	/*
	 * argv[0] must be the perf command, but the argv array
	 * belongs to the caller, and may be reused in
	 * subsequent loop iterations. Save argv[0] and
	 * restore it on error.
	 */
	tmp = argv[0];
	argv[0] = cmd;

	/*
	 * if we fail because the command is not found, it is
	 * OK to return. Otherwise, we just pass along the status code.
	 */
	status = run_command_v_opt(argv, 0);
	if (status != -ERR_RUN_COMMAND_EXEC) {
		if (IS_RUN_COMMAND_ERR(status)) {
do_die:
			pr_err("FATAL: unable to run '%s'", argv[0]);
			status = -128;
		}
		exit(-status);
	}
	errno = ENOENT; /* as if we called execvp */

	argv[0] = tmp;
	zfree(&cmd);
}