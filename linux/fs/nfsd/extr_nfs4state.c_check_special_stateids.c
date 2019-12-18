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
typedef  int /*<<< orphan*/  svc_fh ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_SHARE_DENY_READ ; 
 int /*<<< orphan*/  NFS4_SHARE_DENY_WRITE ; 
 scalar_t__ ONE_STATEID (int /*<<< orphan*/ *) ; 
 int RD_STATE ; 
 int WR_STATE ; 
 int /*<<< orphan*/  nfs4_share_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_grace ; 
 scalar_t__ opens_in_grace (struct net*) ; 

__attribute__((used)) static inline __be32
check_special_stateids(struct net *net, svc_fh *current_fh, stateid_t *stateid, int flags)
{
	if (ONE_STATEID(stateid) && (flags & RD_STATE))
		return nfs_ok;
	else if (opens_in_grace(net)) {
		/* Answer in remaining cases depends on existence of
		 * conflicting state; so we must wait out the grace period. */
		return nfserr_grace;
	} else if (flags & WR_STATE)
		return nfs4_share_conflict(current_fh,
				NFS4_SHARE_DENY_WRITE);
	else /* (flags & RD_STATE) && ZERO_STATEID(stateid) */
		return nfs4_share_conflict(current_fh,
				NFS4_SHARE_DENY_READ);
}