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
 int /*<<< orphan*/  FPM_CLEANUP_PARENT_EXEC ; 
 int /*<<< orphan*/  FPM_EXIT_SOFTWARE ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_cleanups_run (int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_signals_block () ; 
 int /*<<< orphan*/  optional_arg (int) ; 
 int /*<<< orphan*/ * saved_argv ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void fpm_pctl_exec() /* {{{ */
{
	zlog(ZLOG_DEBUG, "Blocking some signals before reexec");
	if (0 > fpm_signals_block()) {
		zlog(ZLOG_WARNING, "concurrent reloads may be unstable");
	}

	zlog(ZLOG_NOTICE, "reloading: execvp(\"%s\", {\"%s\""
			"%s%s%s" "%s%s%s" "%s%s%s" "%s%s%s" "%s%s%s"
			"%s%s%s" "%s%s%s" "%s%s%s" "%s%s%s" "%s%s%s"
		"})",
		saved_argv[0], saved_argv[0],
		optional_arg(1),
		optional_arg(2),
		optional_arg(3),
		optional_arg(4),
		optional_arg(5),
		optional_arg(6),
		optional_arg(7),
		optional_arg(8),
		optional_arg(9),
		optional_arg(10)
	);

	fpm_cleanups_run(FPM_CLEANUP_PARENT_EXEC);
	execvp(saved_argv[0], saved_argv);
	zlog(ZLOG_SYSERROR, "failed to reload: execvp() failed");
	exit(FPM_EXIT_SOFTWARE);
}