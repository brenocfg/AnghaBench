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
struct nfsd_net {int boot_time; int nfsd4_lease; scalar_t__ reclaim_str_hashtbl_size; int somebody_reclaimed; int /*<<< orphan*/  nr_reclaim_complete; scalar_t__ track_reclaim_completes; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long get_seconds () ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static bool clients_still_reclaiming(struct nfsd_net *nn)
{
	unsigned long now = get_seconds();
	unsigned long double_grace_period_end = nn->boot_time +
						2 * nn->nfsd4_lease;

	if (nn->track_reclaim_completes &&
			atomic_read(&nn->nr_reclaim_complete) ==
			nn->reclaim_str_hashtbl_size)
		return false;
	if (!nn->somebody_reclaimed)
		return false;
	nn->somebody_reclaimed = false;
	/*
	 * If we've given them *two* lease times to reclaim, and they're
	 * still not done, give up:
	 */
	if (time_after(now, double_grace_period_end))
		return false;
	return true;
}