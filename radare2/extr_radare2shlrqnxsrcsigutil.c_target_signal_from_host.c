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
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int TARGET_SIGNAL_0 ; 
 int TARGET_SIGNAL_UNKNOWN ; 

enum target_signal
target_signal_from_host (int hostsig) {
	/* A switch statement would make sense but would require special kludges
     to deal with the cases where more than one signal has the same number.  */

	if (hostsig == 0)
		return TARGET_SIGNAL_0;

#if defined(SIGHUP)
	if (hostsig == SIGHUP)
		return TARGET_SIGNAL_HUP;
#endif
#if defined(SIGINT)
	if (hostsig == SIGINT)
		return TARGET_SIGNAL_INT;
#endif
#if defined(SIGQUIT)
	if (hostsig == SIGQUIT)
		return TARGET_SIGNAL_QUIT;
#endif
#if defined(SIGILL)
	if (hostsig == SIGILL)
		return TARGET_SIGNAL_ILL;
#endif
#if defined(SIGTRAP)
	if (hostsig == SIGTRAP)
		return TARGET_SIGNAL_TRAP;
#endif
#if defined(SIGABRT)
	if (hostsig == SIGABRT)
		return TARGET_SIGNAL_ABRT;
#endif
#if defined(SIGEMT)
	if (hostsig == SIGEMT)
		return TARGET_SIGNAL_EMT;
#endif
#if defined(SIGFPE)
	if (hostsig == SIGFPE)
		return TARGET_SIGNAL_FPE;
#endif
#if defined(SIGKILL)
	if (hostsig == SIGKILL)
		return TARGET_SIGNAL_KILL;
#endif
#if defined(SIGBUS)
	if (hostsig == SIGBUS)
		return TARGET_SIGNAL_BUS;
#endif
#if defined(SIGSEGV)
	if (hostsig == SIGSEGV)
		return TARGET_SIGNAL_SEGV;
#endif
#if defined(SIGSYS)
	if (hostsig == SIGSYS)
		return TARGET_SIGNAL_SYS;
#endif
#if defined(SIGPIPE)
	if (hostsig == SIGPIPE)
		return TARGET_SIGNAL_PIPE;
#endif
#if defined(SIGALRM)
	if (hostsig == SIGALRM)
		return TARGET_SIGNAL_ALRM;
#endif
#if defined(SIGTERM)
	if (hostsig == SIGTERM)
		return TARGET_SIGNAL_TERM;
#endif
#if defined(SIGUSR1)
	if (hostsig == SIGUSR1)
		return TARGET_SIGNAL_USR1;
#endif
#if defined(SIGUSR2)
	if (hostsig == SIGUSR2)
		return TARGET_SIGNAL_USR2;
#endif
#if defined(SIGCLD)
	if (hostsig == SIGCLD)
		return TARGET_SIGNAL_CHLD;
#endif
#if defined(SIGCHLD)
	if (hostsig == SIGCHLD)
		return TARGET_SIGNAL_CHLD;
#endif
#if defined(SIGPWR)
	if (hostsig == SIGPWR)
		return TARGET_SIGNAL_PWR;
#endif
#if defined(SIGWINCH)
	if (hostsig == SIGWINCH)
		return TARGET_SIGNAL_WINCH;
#endif
#if defined(SIGURG)
	if (hostsig == SIGURG)
		return TARGET_SIGNAL_URG;
#endif
#if defined(SIGIO)
	if (hostsig == SIGIO)
		return TARGET_SIGNAL_IO;
#endif
#if defined(SIGPOLL)
	if (hostsig == SIGPOLL)
		return TARGET_SIGNAL_POLL;
#endif
#if defined(SIGSTOP)
	if (hostsig == SIGSTOP)
		return TARGET_SIGNAL_STOP;
#endif
#if defined(SIGTSTP)
	if (hostsig == SIGTSTP)
		return TARGET_SIGNAL_TSTP;
#endif
#if defined(SIGCONT)
	if (hostsig == SIGCONT)
		return TARGET_SIGNAL_CONT;
#endif
#if defined(SIGTTIN)
	if (hostsig == SIGTTIN)
		return TARGET_SIGNAL_TTIN;
#endif
#if defined(SIGTTOU)
	if (hostsig == SIGTTOU)
		return TARGET_SIGNAL_TTOU;
#endif
#if defined(SIGVTALRM)
	if (hostsig == SIGVTALRM)
		return TARGET_SIGNAL_VTALRM;
#endif
#if defined(SIGPROF)
	if (hostsig == SIGPROF)
		return TARGET_SIGNAL_PROF;
#endif
#if defined(SIGXCPU)
	if (hostsig == SIGXCPU)
		return TARGET_SIGNAL_XCPU;
#endif
#if defined(SIGXFSZ)
	if (hostsig == SIGXFSZ)
		return TARGET_SIGNAL_XFSZ;
#endif
#if defined(SIGWIND)
	if (hostsig == SIGWIND)
		return TARGET_SIGNAL_WIND;
#endif
#if defined(SIGPHONE)
	if (hostsig == SIGPHONE)
		return TARGET_SIGNAL_PHONE;
#endif
#if defined(SIGLOST)
	if (hostsig == SIGLOST)
		return TARGET_SIGNAL_LOST;
#endif
#if defined(SIGWAITING)
	if (hostsig == SIGWAITING)
		return TARGET_SIGNAL_WAITING;
#endif
#if defined(SIGCANCEL)
	if (hostsig == SIGCANCEL)
		return TARGET_SIGNAL_CANCEL;
#endif
#if defined(SIGLWP)
	if (hostsig == SIGLWP)
		return TARGET_SIGNAL_LWP;
#endif
#if defined(SIGDANGER)
	if (hostsig == SIGDANGER)
		return TARGET_SIGNAL_DANGER;
#endif
#if defined(SIGGRANT)
	if (hostsig == SIGGRANT)
		return TARGET_SIGNAL_GRANT;
#endif
#if defined(SIGRETRACT)
	if (hostsig == SIGRETRACT)
		return TARGET_SIGNAL_RETRACT;
#endif
#if defined(SIGMSG)
	if (hostsig == SIGMSG)
		return TARGET_SIGNAL_MSG;
#endif
#if defined(SIGSOUND)
	if (hostsig == SIGSOUND)
		return TARGET_SIGNAL_SOUND;
#endif
#if defined(SIGSAK)
	if (hostsig == SIGSAK)
		return TARGET_SIGNAL_SAK;
#endif
#if defined(SIGPRIO)
	if (hostsig == SIGPRIO)
		return TARGET_SIGNAL_PRIO;
#endif

/* Mach exceptions.  Assumes that the values for EXC_ are positive! */
#if defined(EXC_BAD_ACCESS) && defined(_NSIG)
	if (hostsig == _NSIG + EXC_BAD_ACCESS)
		return TARGET_EXC_BAD_ACCESS;
#endif
#if defined(EXC_BAD_INSTRUCTION) && defined(_NSIG)
	if (hostsig == _NSIG + EXC_BAD_INSTRUCTION)
		return TARGET_EXC_BAD_INSTRUCTION;
#endif
#if defined(EXC_ARITHMETIC) && defined(_NSIG)
	if (hostsig == _NSIG + EXC_ARITHMETIC)
		return TARGET_EXC_ARITHMETIC;
#endif
#if defined(EXC_EMULATION) && defined(_NSIG)
	if (hostsig == _NSIG + EXC_EMULATION)
		return TARGET_EXC_EMULATION;
#endif
#if defined(EXC_SOFTWARE) && defined(_NSIG)
	if (hostsig == _NSIG + EXC_SOFTWARE)
		return TARGET_EXC_SOFTWARE;
#endif
#if defined(EXC_BREAKPOINT) && defined(_NSIG)
	if (hostsig == _NSIG + EXC_BREAKPOINT)
		return TARGET_EXC_BREAKPOINT;
#endif

#if defined(SIGINFO)
	if (hostsig == SIGINFO)
		return TARGET_SIGNAL_INFO;
#endif

#if defined(REALTIME_LO)
	if (hostsig >= REALTIME_LO && hostsig < REALTIME_HI) {
		/* This block of TARGET_SIGNAL_REALTIME value is in order.  */
		if (33 <= hostsig && hostsig <= 63)
			return (enum target_signal)(hostsig - 33 + (int)TARGET_SIGNAL_REALTIME_33);
		else if (hostsig == 32)
			return TARGET_SIGNAL_REALTIME_32;
		else if (64 <= hostsig && hostsig <= 127)
			return (enum target_signal)(hostsig - 64 + (int)TARGET_SIGNAL_REALTIME_64);
		else
			error ("GDB bug: target.c (target_signal_from_host): unrecognized real-time signal");
	}
#endif

	return TARGET_SIGNAL_UNKNOWN;
}