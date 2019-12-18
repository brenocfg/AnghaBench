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
 int /*<<< orphan*/  BlockSig ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGSYS ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  StartupBlockSig ; 
 int /*<<< orphan*/  UnBlockSig ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

void
pqinitmask(void)
{
	sigemptyset(&UnBlockSig);

	/* First set all signals, then clear some. */
	sigfillset(&BlockSig);
	sigfillset(&StartupBlockSig);

	/*
	 * Unmark those signals that should never be blocked. Some of these signal
	 * names don't exist on all platforms.  Most do, but might as well ifdef
	 * them all for consistency...
	 */
#ifdef SIGTRAP
	sigdelset(&BlockSig, SIGTRAP);
	sigdelset(&StartupBlockSig, SIGTRAP);
#endif
#ifdef SIGABRT
	sigdelset(&BlockSig, SIGABRT);
	sigdelset(&StartupBlockSig, SIGABRT);
#endif
#ifdef SIGILL
	sigdelset(&BlockSig, SIGILL);
	sigdelset(&StartupBlockSig, SIGILL);
#endif
#ifdef SIGFPE
	sigdelset(&BlockSig, SIGFPE);
	sigdelset(&StartupBlockSig, SIGFPE);
#endif
#ifdef SIGSEGV
	sigdelset(&BlockSig, SIGSEGV);
	sigdelset(&StartupBlockSig, SIGSEGV);
#endif
#ifdef SIGBUS
	sigdelset(&BlockSig, SIGBUS);
	sigdelset(&StartupBlockSig, SIGBUS);
#endif
#ifdef SIGSYS
	sigdelset(&BlockSig, SIGSYS);
	sigdelset(&StartupBlockSig, SIGSYS);
#endif
#ifdef SIGCONT
	sigdelset(&BlockSig, SIGCONT);
	sigdelset(&StartupBlockSig, SIGCONT);
#endif

/* Signals unique to startup */
#ifdef SIGQUIT
	sigdelset(&StartupBlockSig, SIGQUIT);
#endif
#ifdef SIGTERM
	sigdelset(&StartupBlockSig, SIGTERM);
#endif
#ifdef SIGALRM
	sigdelset(&StartupBlockSig, SIGALRM);
#endif
}