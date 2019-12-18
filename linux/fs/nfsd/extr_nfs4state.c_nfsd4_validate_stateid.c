#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct nfs4_stid {int sc_type; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_clientid; } ;
struct TYPE_9__ {int /*<<< orphan*/  so_clid; } ;
struct TYPE_10__ {TYPE_1__ si_opaque; } ;
typedef  TYPE_2__ stateid_t ;
typedef  int /*<<< orphan*/  addr_str ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ CLOSE_STATEID (TYPE_2__*) ; 
 int INET6_ADDRSTRLEN ; 
#define  NFS4_CLOSED_DELEG_STID 133 
#define  NFS4_CLOSED_STID 132 
#define  NFS4_DELEG_STID 131 
#define  NFS4_LOCK_STID 130 
#define  NFS4_OPEN_STID 129 
#define  NFS4_REVOKED_DELEG_STID 128 
 scalar_t__ ONE_STATEID (TYPE_2__*) ; 
 scalar_t__ ZERO_STATEID (TYPE_2__*) ; 
 struct nfs4_stid* find_stateid_locked (struct nfs4_client*,TYPE_2__*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_check_openowner_confirmed (int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd4_stid_check_stateid_generation (TYPE_2__*,struct nfs4_stid*,int) ; 
 scalar_t__ nfserr_bad_stateid ; 
 scalar_t__ nfserr_deleg_revoked ; 
 int /*<<< orphan*/  openlockstateid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,char*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  rpc_ntop (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  same_clid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32 nfsd4_validate_stateid(struct nfs4_client *cl, stateid_t *stateid)
{
	struct nfs4_stid *s;
	__be32 status = nfserr_bad_stateid;

	if (ZERO_STATEID(stateid) || ONE_STATEID(stateid) ||
		CLOSE_STATEID(stateid))
		return status;
	/* Client debugging aid. */
	if (!same_clid(&stateid->si_opaque.so_clid, &cl->cl_clientid)) {
		char addr_str[INET6_ADDRSTRLEN];
		rpc_ntop((struct sockaddr *)&cl->cl_addr, addr_str,
				 sizeof(addr_str));
		pr_warn_ratelimited("NFSD: client %s testing state ID "
					"with incorrect client ID\n", addr_str);
		return status;
	}
	spin_lock(&cl->cl_lock);
	s = find_stateid_locked(cl, stateid);
	if (!s)
		goto out_unlock;
	status = nfsd4_stid_check_stateid_generation(stateid, s, 1);
	if (status)
		goto out_unlock;
	switch (s->sc_type) {
	case NFS4_DELEG_STID:
		status = nfs_ok;
		break;
	case NFS4_REVOKED_DELEG_STID:
		status = nfserr_deleg_revoked;
		break;
	case NFS4_OPEN_STID:
	case NFS4_LOCK_STID:
		status = nfsd4_check_openowner_confirmed(openlockstateid(s));
		break;
	default:
		printk("unknown stateid type %x\n", s->sc_type);
		/* Fallthrough */
	case NFS4_CLOSED_STID:
	case NFS4_CLOSED_DELEG_STID:
		status = nfserr_bad_stateid;
	}
out_unlock:
	spin_unlock(&cl->cl_lock);
	return status;
}