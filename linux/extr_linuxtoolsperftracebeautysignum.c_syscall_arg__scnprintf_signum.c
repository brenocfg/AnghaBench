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
struct syscall_arg {int val; } ;

/* Variables and functions */
#define  SIGABRT 157 
#define  SIGALRM 156 
#define  SIGBUS 155 
#define  SIGCHLD 154 
#define  SIGCONT 153 
#define  SIGFPE 152 
#define  SIGHUP 151 
#define  SIGILL 150 
#define  SIGINT 149 
#define  SIGIO 148 
#define  SIGKILL 147 
#define  SIGPIPE 146 
#define  SIGPROF 145 
#define  SIGPWR 144 
#define  SIGQUIT 143 
#define  SIGSEGV 142 
#define  SIGSTOP 141 
#define  SIGSYS 140 
#define  SIGTERM 139 
#define  SIGTRAP 138 
#define  SIGTSTP 137 
#define  SIGTTIN 136 
#define  SIGTTOU 135 
#define  SIGURG 134 
#define  SIGUSR1 133 
#define  SIGUSR2 132 
#define  SIGVTALRM 131 
#define  SIGWINCH 130 
#define  SIGXCPU 129 
#define  SIGXFSZ 128 
 size_t scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_signum(char *bf, size_t size, struct syscall_arg *arg)
{
	int sig = arg->val;

	switch (sig) {
#define	P_SIGNUM(n) case SIG##n: return scnprintf(bf, size, #n)
	P_SIGNUM(HUP);
	P_SIGNUM(INT);
	P_SIGNUM(QUIT);
	P_SIGNUM(ILL);
	P_SIGNUM(TRAP);
	P_SIGNUM(ABRT);
	P_SIGNUM(BUS);
	P_SIGNUM(FPE);
	P_SIGNUM(KILL);
	P_SIGNUM(USR1);
	P_SIGNUM(SEGV);
	P_SIGNUM(USR2);
	P_SIGNUM(PIPE);
	P_SIGNUM(ALRM);
	P_SIGNUM(TERM);
	P_SIGNUM(CHLD);
	P_SIGNUM(CONT);
	P_SIGNUM(STOP);
	P_SIGNUM(TSTP);
	P_SIGNUM(TTIN);
	P_SIGNUM(TTOU);
	P_SIGNUM(URG);
	P_SIGNUM(XCPU);
	P_SIGNUM(XFSZ);
	P_SIGNUM(VTALRM);
	P_SIGNUM(PROF);
	P_SIGNUM(WINCH);
	P_SIGNUM(IO);
	P_SIGNUM(PWR);
	P_SIGNUM(SYS);
#ifdef SIGEMT
	P_SIGNUM(EMT);
#endif
#ifdef SIGSTKFLT
	P_SIGNUM(STKFLT);
#endif
#ifdef SIGSWI
	P_SIGNUM(SWI);
#endif
	default: break;
	}

	return scnprintf(bf, size, "%#x", sig);
}