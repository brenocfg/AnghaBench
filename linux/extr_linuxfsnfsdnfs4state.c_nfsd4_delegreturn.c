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
struct nfsd4_delegreturn {int /*<<< orphan*/  dr_stateid; } ;
union nfsd4_op_u {struct nfsd4_delegreturn delegreturn; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
struct nfs4_stid {int dummy; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_stid; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_DELEG_STID ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  S_IFREG ; 
 struct nfs4_delegation* delegstateid (struct nfs4_stid*) ; 
 int /*<<< orphan*/  destroy_delegation (struct nfs4_delegation*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_put_stid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_has_session (struct nfsd4_compound_state*) ; 
 scalar_t__ nfsd4_lookup_stateid (struct nfsd4_compound_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfs4_stid**,struct nfsd_net*) ; 
 scalar_t__ nfsd4_stid_check_stateid_generation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

__be32
nfsd4_delegreturn(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		  union nfsd4_op_u *u)
{
	struct nfsd4_delegreturn *dr = &u->delegreturn;
	struct nfs4_delegation *dp;
	stateid_t *stateid = &dr->dr_stateid;
	struct nfs4_stid *s;
	__be32 status;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	if ((status = fh_verify(rqstp, &cstate->current_fh, S_IFREG, 0)))
		return status;

	status = nfsd4_lookup_stateid(cstate, stateid, NFS4_DELEG_STID, &s, nn);
	if (status)
		goto out;
	dp = delegstateid(s);
	status = nfsd4_stid_check_stateid_generation(stateid, &dp->dl_stid, nfsd4_has_session(cstate));
	if (status)
		goto put_stateid;

	destroy_delegation(dp);
put_stateid:
	nfs4_put_stid(&dp->dl_stid);
out:
	return status;
}