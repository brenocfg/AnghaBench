#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct fown_struct {int /*<<< orphan*/  signum; } ;
struct TYPE_5__ {int si_signo; int si_code; long si_band; int si_fd; int /*<<< orphan*/  si_errno; } ;
typedef  TYPE_1__ kernel_siginfo_t ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NSIGPOLL ; 
 int POLL_IN ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_1__* SEND_SIG_PRIV ; 
 int SIGIO ; 
 int SIGPOLL ; 
 int SI_SIGIO ; 
 int /*<<< orphan*/ * band_table ; 
 int /*<<< orphan*/  clear_siginfo (TYPE_1__*) ; 
 int /*<<< orphan*/  do_send_sig_info (int,TYPE_1__*,struct task_struct*,int) ; 
 long mangle_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sig_specific_sicodes (int) ; 
 int /*<<< orphan*/  sigio_perm (struct task_struct*,struct fown_struct*,int) ; 

__attribute__((used)) static void send_sigio_to_task(struct task_struct *p,
			       struct fown_struct *fown,
			       int fd, int reason, enum pid_type type)
{
	/*
	 * F_SETSIG can change ->signum lockless in parallel, make
	 * sure we read it once and use the same value throughout.
	 */
	int signum = READ_ONCE(fown->signum);

	if (!sigio_perm(p, fown, signum))
		return;

	switch (signum) {
		kernel_siginfo_t si;
		default:
			/* Queue a rt signal with the appropriate fd as its
			   value.  We use SI_SIGIO as the source, not 
			   SI_KERNEL, since kernel signals always get 
			   delivered even if we can't queue.  Failure to
			   queue in this case _should_ be reported; we fall
			   back to SIGIO in that case. --sct */
			clear_siginfo(&si);
			si.si_signo = signum;
			si.si_errno = 0;
		        si.si_code  = reason;
			/*
			 * Posix definies POLL_IN and friends to be signal
			 * specific si_codes for SIG_POLL.  Linux extended
			 * these si_codes to other signals in a way that is
			 * ambiguous if other signals also have signal
			 * specific si_codes.  In that case use SI_SIGIO instead
			 * to remove the ambiguity.
			 */
			if ((signum != SIGPOLL) && sig_specific_sicodes(signum))
				si.si_code = SI_SIGIO;

			/* Make sure we are called with one of the POLL_*
			   reasons, otherwise we could leak kernel stack into
			   userspace.  */
			BUG_ON((reason < POLL_IN) || ((reason - POLL_IN) >= NSIGPOLL));
			if (reason - POLL_IN >= NSIGPOLL)
				si.si_band  = ~0L;
			else
				si.si_band = mangle_poll(band_table[reason - POLL_IN]);
			si.si_fd    = fd;
			if (!do_send_sig_info(signum, &si, p, type))
				break;
		/* fall-through - fall back on the old plain SIGIO signal */
		case 0:
			do_send_sig_info(SIGIO, SEND_SIG_PRIV, p, type);
	}
}