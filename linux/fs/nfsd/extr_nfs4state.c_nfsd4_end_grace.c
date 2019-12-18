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
struct nfsd_net {int grace_ended; int /*<<< orphan*/  nfsd4_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  locks_end_grace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_record_grace_done (struct nfsd_net*) ; 

void
nfsd4_end_grace(struct nfsd_net *nn)
{
	/* do nothing if grace period already ended */
	if (nn->grace_ended)
		return;

	nn->grace_ended = true;
	/*
	 * If the server goes down again right now, an NFSv4
	 * client will still be allowed to reclaim after it comes back up,
	 * even if it hasn't yet had a chance to reclaim state this time.
	 *
	 */
	nfsd4_record_grace_done(nn);
	/*
	 * At this point, NFSv4 clients can still reclaim.  But if the
	 * server crashes, any that have not yet reclaimed will be out
	 * of luck on the next boot.
	 *
	 * (NFSv4.1+ clients are considered to have reclaimed once they
	 * call RECLAIM_COMPLETE.  NFSv4.0 clients are considered to
	 * have reclaimed after their first OPEN.)
	 */
	locks_end_grace(&nn->nfsd4_manager);
	/*
	 * At this point, and once lockd and/or any other containers
	 * exit their grace period, further reclaims will fail and
	 * regular locking can resume.
	 */
}