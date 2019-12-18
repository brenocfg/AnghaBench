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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  act ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 scalar_t__ fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fd_set_blocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_signals_unblock () ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sig_handler ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sp ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

int fpm_signals_init_main() /* {{{ */
{
	struct sigaction act;

	if (0 > socketpair(AF_UNIX, SOCK_STREAM, 0, sp)) {
		zlog(ZLOG_SYSERROR, "failed to init signals: socketpair()");
		return -1;
	}

	if (0 > fd_set_blocked(sp[0], 0) || 0 > fd_set_blocked(sp[1], 0)) {
		zlog(ZLOG_SYSERROR, "failed to init signals: fd_set_blocked()");
		return -1;
	}

	if (0 > fcntl(sp[0], F_SETFD, FD_CLOEXEC) || 0 > fcntl(sp[1], F_SETFD, FD_CLOEXEC)) {
		zlog(ZLOG_SYSERROR, "falied to init signals: fcntl(F_SETFD, FD_CLOEXEC)");
		return -1;
	}

	memset(&act, 0, sizeof(act));
	act.sa_handler = sig_handler;
	sigfillset(&act.sa_mask);

	if (0 > sigaction(SIGTERM,  &act, 0) ||
	    0 > sigaction(SIGINT,   &act, 0) ||
	    0 > sigaction(SIGUSR1,  &act, 0) ||
	    0 > sigaction(SIGUSR2,  &act, 0) ||
	    0 > sigaction(SIGCHLD,  &act, 0) ||
	    0 > sigaction(SIGQUIT,  &act, 0)) {

		zlog(ZLOG_SYSERROR, "failed to init signals: sigaction()");
		return -1;
	}

	zlog(ZLOG_DEBUG, "Unblocking all signals");
	if (0 > fpm_signals_unblock()) {
		return -1;
	}
	return 0;
}