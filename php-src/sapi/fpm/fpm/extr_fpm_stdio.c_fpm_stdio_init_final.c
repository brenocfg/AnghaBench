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
struct TYPE_2__ {scalar_t__ error_log_fd; } ;

/* Variables and functions */
 scalar_t__ STDERR_FILENO ; 
 scalar_t__ STDOUT_FILENO ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 scalar_t__ ZLOG_SYSLOG ; 
 scalar_t__ dup2 (scalar_t__,scalar_t__) ; 
 TYPE_1__ fpm_globals ; 
 scalar_t__ fpm_use_error_log () ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zlog_set_launched () ; 

int fpm_stdio_init_final() /* {{{ */
{
	if (fpm_use_error_log()) {
		/* prevent duping if logging to syslog */
		if (fpm_globals.error_log_fd > 0 && fpm_globals.error_log_fd != STDERR_FILENO) {

			/* there might be messages to stderr from other parts of the code, we need to log them all */
			if (0 > dup2(fpm_globals.error_log_fd, STDERR_FILENO)) {
				zlog(ZLOG_SYSERROR, "failed to init stdio: dup2()");
				return -1;
			}
		}
#ifdef HAVE_SYSLOG_H
		else if (fpm_globals.error_log_fd == ZLOG_SYSLOG) {
			/* dup to /dev/null when using syslog */
			dup2(STDOUT_FILENO, STDERR_FILENO);
		}
#endif
	}
	zlog_set_launched();
	return 0;
}