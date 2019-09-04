#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ si_generation; } ;
typedef  TYPE_1__ stateid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_ok ; 
 scalar_t__ nfsd4_stateid_generation_after (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nfserr_bad_stateid ; 
 int /*<<< orphan*/  nfserr_old_stateid ; 

__attribute__((used)) static __be32 check_stateid_generation(stateid_t *in, stateid_t *ref, bool has_session)
{
	/*
	 * When sessions are used the stateid generation number is ignored
	 * when it is zero.
	 */
	if (has_session && in->si_generation == 0)
		return nfs_ok;

	if (in->si_generation == ref->si_generation)
		return nfs_ok;

	/* If the client sends us a stateid from the future, it's buggy: */
	if (nfsd4_stateid_generation_after(in, ref))
		return nfserr_bad_stateid;
	/*
	 * However, we could see a stateid from the past, even from a
	 * non-buggy client.  For example, if the client sends a lock
	 * while some IO is outstanding, the lock may bump si_generation
	 * while the IO is still in flight.  The client could avoid that
	 * situation by waiting for responses on all the IO requests,
	 * but better performance may result in retrying IO that
	 * receives an old_stateid error if requests are rarely
	 * reordered in flight:
	 */
	return nfserr_old_stateid;
}