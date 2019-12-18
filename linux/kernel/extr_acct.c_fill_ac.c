#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
typedef  scalar_t__ u16 ;
struct tty_struct {int dummy; } ;
struct pacct_struct {unsigned long ac_utime; unsigned long ac_stime; unsigned long ac_mem; unsigned long ac_minflt; unsigned long ac_majflt; int /*<<< orphan*/  ac_exitcode; int /*<<< orphan*/  ac_flag; } ;
typedef  int comp2_t ;
struct TYPE_11__ {int ac_version; int ac_etime_hi; int /*<<< orphan*/  ac_exitcode; void* ac_majflt; void* ac_minflt; void* ac_mem; int /*<<< orphan*/  ac_flag; void* ac_stime; void* ac_utime; int /*<<< orphan*/  ac_tty; int /*<<< orphan*/  ac_ahz; scalar_t__ ac_btime; scalar_t__ ac_etime_lo; void* ac_etime; int /*<<< orphan*/  ac_comm; } ;
typedef  TYPE_4__ acct_t ;
struct TYPE_12__ {TYPE_3__* sighand; TYPE_2__* signal; TYPE_1__* group_leader; int /*<<< orphan*/  comm; } ;
struct TYPE_10__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_9__ {struct tty_struct* tty; struct pacct_struct pacct; } ;
struct TYPE_8__ {scalar_t__ start_time; } ;

/* Variables and functions */
 int ACCT_BYTEORDER ; 
 int ACCT_VERSION ; 
 int /*<<< orphan*/  AHZ ; 
 TYPE_7__* current ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 
 int encode_comp2_t (unsigned long) ; 
 void* encode_comp_t (unsigned long) ; 
 void* encode_float (unsigned long) ; 
 scalar_t__ get_seconds () ; 
 unsigned long ktime_get_ns () ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 unsigned long nsec_to_AHZ (unsigned long) ; 
 int /*<<< orphan*/  old_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_devnum (struct tty_struct*) ; 

__attribute__((used)) static void fill_ac(acct_t *ac)
{
	struct pacct_struct *pacct = &current->signal->pacct;
	u64 elapsed, run_time;
	struct tty_struct *tty;

	/*
	 * Fill the accounting struct with the needed info as recorded
	 * by the different kernel functions.
	 */
	memset(ac, 0, sizeof(acct_t));

	ac->ac_version = ACCT_VERSION | ACCT_BYTEORDER;
	strlcpy(ac->ac_comm, current->comm, sizeof(ac->ac_comm));

	/* calculate run_time in nsec*/
	run_time = ktime_get_ns();
	run_time -= current->group_leader->start_time;
	/* convert nsec -> AHZ */
	elapsed = nsec_to_AHZ(run_time);
#if ACCT_VERSION == 3
	ac->ac_etime = encode_float(elapsed);
#else
	ac->ac_etime = encode_comp_t(elapsed < (unsigned long) -1l ?
				(unsigned long) elapsed : (unsigned long) -1l);
#endif
#if ACCT_VERSION == 1 || ACCT_VERSION == 2
	{
		/* new enlarged etime field */
		comp2_t etime = encode_comp2_t(elapsed);

		ac->ac_etime_hi = etime >> 16;
		ac->ac_etime_lo = (u16) etime;
	}
#endif
	do_div(elapsed, AHZ);
	ac->ac_btime = get_seconds() - elapsed;
#if ACCT_VERSION==2
	ac->ac_ahz = AHZ;
#endif

	spin_lock_irq(&current->sighand->siglock);
	tty = current->signal->tty;	/* Safe as we hold the siglock */
	ac->ac_tty = tty ? old_encode_dev(tty_devnum(tty)) : 0;
	ac->ac_utime = encode_comp_t(nsec_to_AHZ(pacct->ac_utime));
	ac->ac_stime = encode_comp_t(nsec_to_AHZ(pacct->ac_stime));
	ac->ac_flag = pacct->ac_flag;
	ac->ac_mem = encode_comp_t(pacct->ac_mem);
	ac->ac_minflt = encode_comp_t(pacct->ac_minflt);
	ac->ac_majflt = encode_comp_t(pacct->ac_majflt);
	ac->ac_exitcode = pacct->ac_exitcode;
	spin_unlock_irq(&current->sighand->siglock);
}