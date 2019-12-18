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
struct sigaction {int /*<<< orphan*/ * sa_handler; int /*<<< orphan*/  sa_flags; } ;
typedef  int /*<<< orphan*/  act_dfl ;
typedef  int /*<<< orphan*/  act ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/ * SIG_DFL ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sig_soft_quit ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sp ; 
 int /*<<< orphan*/  zend_signal_init () ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

int fpm_signals_init_child() /* {{{ */
{
	struct sigaction act, act_dfl;

	memset(&act, 0, sizeof(act));
	memset(&act_dfl, 0, sizeof(act_dfl));

	act.sa_handler = &sig_soft_quit;
	act.sa_flags |= SA_RESTART;

	act_dfl.sa_handler = SIG_DFL;

	close(sp[0]);
	close(sp[1]);

	if (0 > sigaction(SIGTERM,  &act_dfl,  0) ||
	    0 > sigaction(SIGINT,   &act_dfl,  0) ||
	    0 > sigaction(SIGUSR1,  &act_dfl,  0) ||
	    0 > sigaction(SIGUSR2,  &act_dfl,  0) ||
	    0 > sigaction(SIGCHLD,  &act_dfl,  0) ||
	    0 > sigaction(SIGQUIT,  &act,      0)) {

		zlog(ZLOG_SYSERROR, "failed to init child signals: sigaction()");
		return -1;
	}

	zend_signal_init();
	return 0;
}