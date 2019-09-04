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
typedef  int /*<<< orphan*/  zend_long ;

/* Variables and functions */

__attribute__((used)) static void zend_set_timeout_ex(zend_long seconds, int reset_signals) /* {{{ */
{
#ifdef ZEND_WIN32
	zend_executor_globals *eg;

	if(!seconds) {
		return;
	}

        /* Don't use ChangeTimerQueueTimer() as it will not restart an expired
		timer, so we could end up with just an ignored timeout. Instead
		delete and recreate. */
	if (NULL != tq_timer) {
		if (!DeleteTimerQueueTimer(NULL, tq_timer, INVALID_HANDLE_VALUE)) {
			tq_timer = NULL;
			zend_error_noreturn(E_ERROR, "Could not delete queued timer");
			return;
		}
		tq_timer = NULL;
	}

	/* XXX passing NULL means the default timer queue provided by the system is used */
	eg = ZEND_MODULE_GLOBALS_BULK(executor);
	if (!CreateTimerQueueTimer(&tq_timer, NULL, (WAITORTIMERCALLBACK)tq_timer_cb, (VOID*)eg, seconds*1000, 0, WT_EXECUTEONLYONCE)) {
		tq_timer = NULL;
		zend_error_noreturn(E_ERROR, "Could not queue new timer");
		return;
	}
#else
#	ifdef HAVE_SETITIMER
	{
		struct itimerval t_r;		/* timeout requested */
		int signo;

		if(seconds) {
			t_r.it_value.tv_sec = seconds;
			t_r.it_value.tv_usec = t_r.it_interval.tv_sec = t_r.it_interval.tv_usec = 0;

#	ifdef __CYGWIN__
			setitimer(ITIMER_REAL, &t_r, NULL);
		}
		signo = SIGALRM;
#	else
			setitimer(ITIMER_PROF, &t_r, NULL);
		}
		signo = SIGPROF;
#	endif

		if (reset_signals) {
#	ifdef ZEND_SIGNALS
			zend_signal(signo, zend_timeout_handler);
#	else
			sigset_t sigset;
#   ifdef HAVE_SIGACTION
			struct sigaction act;

			act.sa_handler = zend_timeout_handler;
			sigemptyset(&act.sa_mask);
			act.sa_flags = SA_RESETHAND | SA_NODEFER;
			sigaction(signo, &act, NULL);
#   else
			signal(signo, zend_timeout_handler);
#   endif /* HAVE_SIGACTION */
			sigemptyset(&sigset);
			sigaddset(&sigset, signo);
			sigprocmask(SIG_UNBLOCK, &sigset, NULL);
#	endif /* ZEND_SIGNALS */
		}
	}
#	endif /* HAVE_SETITIMER */
#endif
}