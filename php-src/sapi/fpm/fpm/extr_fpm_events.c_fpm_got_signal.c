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
struct fpm_event_s {int fd; } ;
struct TYPE_2__ {scalar_t__ is_child; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FPM_PCTL_ACTION_SET ; 
 int /*<<< orphan*/  FPM_PCTL_STATE_FINISHING ; 
 int /*<<< orphan*/  FPM_PCTL_STATE_RELOADING ; 
 int /*<<< orphan*/  FPM_PCTL_STATE_TERMINATING ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  children_bury_timer ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fpm_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_event_set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ fpm_globals ; 
 int fpm_log_open (int) ; 
 int /*<<< orphan*/  fpm_pctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_postponed_children_bury ; 
 int /*<<< orphan*/  fpm_stdio_open_error_log (int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fpm_got_signal(struct fpm_event_s *ev, short which, void *arg) /* {{{ */
{
	char c;
	int res, ret;
	int fd = ev->fd;

	do {
		do {
			res = read(fd, &c, 1);
		} while (res == -1 && errno == EINTR);

		if (res <= 0) {
			if (res < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
				zlog(ZLOG_SYSERROR, "unable to read from the signal pipe");
			}
			return;
		}

		switch (c) {
			case 'C' :                  /* SIGCHLD */
				zlog(ZLOG_DEBUG, "received SIGCHLD");
				/* epoll_wait() may report signal fd before read events for a finished child
				 * in the same bunch of events. Prevent immediate free of the child structure
				 * and so the fpm_event_s instance. Otherwise use after free happens during
				 * attemp to process following read event. */
				fpm_event_set_timer(&children_bury_timer, 0, &fpm_postponed_children_bury, NULL);
				fpm_event_add(&children_bury_timer, 0);
				break;
			case 'I' :                  /* SIGINT  */
				zlog(ZLOG_DEBUG, "received SIGINT");
				zlog(ZLOG_NOTICE, "Terminating ...");
				fpm_pctl(FPM_PCTL_STATE_TERMINATING, FPM_PCTL_ACTION_SET);
				break;
			case 'T' :                  /* SIGTERM */
				zlog(ZLOG_DEBUG, "received SIGTERM");
				zlog(ZLOG_NOTICE, "Terminating ...");
				fpm_pctl(FPM_PCTL_STATE_TERMINATING, FPM_PCTL_ACTION_SET);
				break;
			case 'Q' :                  /* SIGQUIT */
				zlog(ZLOG_DEBUG, "received SIGQUIT");
				zlog(ZLOG_NOTICE, "Finishing ...");
				fpm_pctl(FPM_PCTL_STATE_FINISHING, FPM_PCTL_ACTION_SET);
				break;
			case '1' :                  /* SIGUSR1 */
				zlog(ZLOG_DEBUG, "received SIGUSR1");
				if (0 == fpm_stdio_open_error_log(1)) {
					zlog(ZLOG_NOTICE, "error log file re-opened");
				} else {
					zlog(ZLOG_ERROR, "unable to re-opened error log file");
				}

				ret = fpm_log_open(1);
				if (ret == 0) {
					zlog(ZLOG_NOTICE, "access log file re-opened");
				} else if (ret == -1) {
					zlog(ZLOG_ERROR, "unable to re-opened access log file");
				}
				/* else no access log are set */

				break;
			case '2' :                  /* SIGUSR2 */
				zlog(ZLOG_DEBUG, "received SIGUSR2");
				zlog(ZLOG_NOTICE, "Reloading in progress ...");
				fpm_pctl(FPM_PCTL_STATE_RELOADING, FPM_PCTL_ACTION_SET);
				break;
		}

		if (fpm_globals.is_child) {
			break;
		}
	} while (1);
	return;
}