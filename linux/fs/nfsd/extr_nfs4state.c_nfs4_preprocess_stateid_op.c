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
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_dentry; } ;
struct nfsd_net {int dummy; } ;
struct nfsd_file {int dummy; } ;
struct nfsd4_compound_state {int dummy; } ;
struct nfs4_stid {int sc_type; } ;
struct net {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
#define  NFS4_DELEG_STID 130 
#define  NFS4_LOCK_STID 129 
#define  NFS4_OPEN_STID 128 
 scalar_t__ ONE_STATEID (int /*<<< orphan*/ *) ; 
 struct net* SVC_NET (struct svc_rqst*) ; 
 scalar_t__ ZERO_STATEID (int /*<<< orphan*/ *) ; 
 scalar_t__ check_special_stateids (struct net*,struct svc_fh*,int /*<<< orphan*/ *,int) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegstateid (struct nfs4_stid*) ; 
 scalar_t__ grace_disallows_io (struct net*,struct inode*) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_check_delegmode (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfs4_check_fh (struct svc_fh*,struct nfs4_stid*) ; 
 scalar_t__ nfs4_check_file (struct svc_rqst*,struct svc_fh*,struct nfs4_stid*,struct nfsd_file**,int) ; 
 scalar_t__ nfs4_check_olstateid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs4_put_stid (struct nfs4_stid*) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_has_session (struct nfsd4_compound_state*) ; 
 scalar_t__ nfsd4_lookup_stateid (struct nfsd4_compound_state*,int /*<<< orphan*/ *,int,struct nfs4_stid**,struct nfsd_net*) ; 
 scalar_t__ nfsd4_stid_check_stateid_generation (int /*<<< orphan*/ *,struct nfs4_stid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 scalar_t__ nfserr_bad_stateid ; 
 scalar_t__ nfserr_grace ; 
 int /*<<< orphan*/  openlockstateid (struct nfs4_stid*) ; 

__be32
nfs4_preprocess_stateid_op(struct svc_rqst *rqstp,
		struct nfsd4_compound_state *cstate, struct svc_fh *fhp,
		stateid_t *stateid, int flags, struct nfsd_file **nfp)
{
	struct inode *ino = d_inode(fhp->fh_dentry);
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	struct nfs4_stid *s = NULL;
	__be32 status;

	if (nfp)
		*nfp = NULL;

	if (grace_disallows_io(net, ino))
		return nfserr_grace;

	if (ZERO_STATEID(stateid) || ONE_STATEID(stateid)) {
		status = check_special_stateids(net, fhp, stateid, flags);
		goto done;
	}

	status = nfsd4_lookup_stateid(cstate, stateid,
				NFS4_DELEG_STID|NFS4_OPEN_STID|NFS4_LOCK_STID,
				&s, nn);
	if (status)
		return status;
	status = nfsd4_stid_check_stateid_generation(stateid, s,
			nfsd4_has_session(cstate));
	if (status)
		goto out;

	switch (s->sc_type) {
	case NFS4_DELEG_STID:
		status = nfs4_check_delegmode(delegstateid(s), flags);
		break;
	case NFS4_OPEN_STID:
	case NFS4_LOCK_STID:
		status = nfs4_check_olstateid(openlockstateid(s), flags);
		break;
	default:
		status = nfserr_bad_stateid;
		break;
	}
	if (status)
		goto out;
	status = nfs4_check_fh(fhp, s);

done:
	if (status == nfs_ok && nfp)
		status = nfs4_check_file(rqstp, fhp, s, nfp, flags);
out:
	if (s)
		nfs4_put_stid(s);
	return status;
}