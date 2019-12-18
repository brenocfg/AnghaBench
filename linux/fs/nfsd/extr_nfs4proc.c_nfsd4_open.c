#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct nfsd4_open {int op_claim_type; scalar_t__ op_xdr_error; scalar_t__ op_created; TYPE_4__* op_openowner; int /*<<< orphan*/  op_clientid; scalar_t__ op_create; TYPE_1__ op_fname; } ;
union nfsd4_op_u {struct nfsd4_open open; } ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_handle; } ;
struct nfsd_net {int somebody_reclaimed; } ;
struct nfsd4_compound_state {struct svc_fh current_fh; TYPE_5__* session; } ;
struct nfs4_replay {int /*<<< orphan*/  rp_openfh; } ;
struct net {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_10__ {TYPE_2__* se_client; } ;
struct TYPE_8__ {struct nfs4_replay so_replay; } ;
struct TYPE_9__ {int /*<<< orphan*/  oo_flags; TYPE_3__ oo_owner; } ;
struct TYPE_7__ {int /*<<< orphan*/  cl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OO_CONFIRMED ; 
#define  NFS4_OPEN_CLAIM_DELEGATE_CUR 134 
#define  NFS4_OPEN_CLAIM_DELEGATE_PREV 133 
#define  NFS4_OPEN_CLAIM_DELEG_CUR_FH 132 
#define  NFS4_OPEN_CLAIM_DELEG_PREV_FH 131 
#define  NFS4_OPEN_CLAIM_FH 130 
#define  NFS4_OPEN_CLAIM_NULL 129 
#define  NFS4_OPEN_CLAIM_PREVIOUS 128 
 int /*<<< orphan*/  NFSD4_CLIENT_RECLAIM_COMPLETE ; 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 struct net* SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  copy_clientid (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ do_open_fhandle (struct svc_rqst*,struct nfsd4_compound_state*,struct nfsd4_open*) ; 
 scalar_t__ do_open_lookup (struct svc_rqst*,struct nfsd4_compound_state*,struct nfsd4_open*,struct svc_fh**) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  fh_copy_shallow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_dup2 (struct svc_fh*,struct svc_fh*) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct svc_fh*) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_check_open_reclaim (int /*<<< orphan*/ *,struct nfsd4_compound_state*,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfsd4_bump_seqid (struct nfsd4_compound_state*,scalar_t__) ; 
 scalar_t__ nfsd4_check_open_attributes (struct svc_rqst*,struct nfsd4_compound_state*,struct nfsd4_open*) ; 
 int /*<<< orphan*/  nfsd4_cleanup_open_state (struct nfsd4_compound_state*,struct nfsd4_open*) ; 
 scalar_t__ nfsd4_has_session (struct nfsd4_compound_state*) ; 
 scalar_t__ nfsd4_process_open1 (struct nfsd4_compound_state*,struct nfsd4_open*,struct nfsd_net*) ; 
 scalar_t__ nfsd4_process_open2 (struct svc_rqst*,struct svc_fh*,struct nfsd4_open*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 scalar_t__ nfserr_grace ; 
 scalar_t__ nfserr_inval ; 
 scalar_t__ nfserr_no_grace ; 
 scalar_t__ nfserr_notsupp ; 
 scalar_t__ nfserr_replay_me ; 
 scalar_t__ opens_in_grace (struct net*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_open(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	   union nfsd4_op_u *u)
{
	struct nfsd4_open *open = &u->open;
	__be32 status;
	struct svc_fh *resfh = NULL;
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	bool reclaim = false;

	dprintk("NFSD: nfsd4_open filename %.*s op_openowner %p\n",
		(int)open->op_fname.len, open->op_fname.data,
		open->op_openowner);

	/* This check required by spec. */
	if (open->op_create && open->op_claim_type != NFS4_OPEN_CLAIM_NULL)
		return nfserr_inval;

	open->op_created = 0;
	/*
	 * RFC5661 18.51.3
	 * Before RECLAIM_COMPLETE done, server should deny new lock
	 */
	if (nfsd4_has_session(cstate) &&
	    !test_bit(NFSD4_CLIENT_RECLAIM_COMPLETE,
		      &cstate->session->se_client->cl_flags) &&
	    open->op_claim_type != NFS4_OPEN_CLAIM_PREVIOUS)
		return nfserr_grace;

	if (nfsd4_has_session(cstate))
		copy_clientid(&open->op_clientid, cstate->session);

	/* check seqid for replay. set nfs4_owner */
	status = nfsd4_process_open1(cstate, open, nn);
	if (status == nfserr_replay_me) {
		struct nfs4_replay *rp = &open->op_openowner->oo_owner.so_replay;
		fh_put(&cstate->current_fh);
		fh_copy_shallow(&cstate->current_fh.fh_handle,
				&rp->rp_openfh);
		status = fh_verify(rqstp, &cstate->current_fh, 0, NFSD_MAY_NOP);
		if (status)
			dprintk("nfsd4_open: replay failed"
				" restoring previous filehandle\n");
		else
			status = nfserr_replay_me;
	}
	if (status)
		goto out;
	if (open->op_xdr_error) {
		status = open->op_xdr_error;
		goto out;
	}

	status = nfsd4_check_open_attributes(rqstp, cstate, open);
	if (status)
		goto out;

	/* Openowner is now set, so sequence id will get bumped.  Now we need
	 * these checks before we do any creates: */
	status = nfserr_grace;
	if (opens_in_grace(net) && open->op_claim_type != NFS4_OPEN_CLAIM_PREVIOUS)
		goto out;
	status = nfserr_no_grace;
	if (!opens_in_grace(net) && open->op_claim_type == NFS4_OPEN_CLAIM_PREVIOUS)
		goto out;

	switch (open->op_claim_type) {
		case NFS4_OPEN_CLAIM_DELEGATE_CUR:
		case NFS4_OPEN_CLAIM_NULL:
			status = do_open_lookup(rqstp, cstate, open, &resfh);
			if (status)
				goto out;
			break;
		case NFS4_OPEN_CLAIM_PREVIOUS:
			status = nfs4_check_open_reclaim(&open->op_clientid,
							 cstate, nn);
			if (status)
				goto out;
			open->op_openowner->oo_flags |= NFS4_OO_CONFIRMED;
			reclaim = true;
			/* fall through */
		case NFS4_OPEN_CLAIM_FH:
		case NFS4_OPEN_CLAIM_DELEG_CUR_FH:
			status = do_open_fhandle(rqstp, cstate, open);
			if (status)
				goto out;
			resfh = &cstate->current_fh;
			break;
		case NFS4_OPEN_CLAIM_DELEG_PREV_FH:
             	case NFS4_OPEN_CLAIM_DELEGATE_PREV:
			dprintk("NFSD: unsupported OPEN claim type %d\n",
				open->op_claim_type);
			status = nfserr_notsupp;
			goto out;
		default:
			dprintk("NFSD: Invalid OPEN claim type %d\n",
				open->op_claim_type);
			status = nfserr_inval;
			goto out;
	}
	/*
	 * nfsd4_process_open2() does the actual opening of the file.  If
	 * successful, it (1) truncates the file if open->op_truncate was
	 * set, (2) sets open->op_stateid, (3) sets open->op_delegation.
	 */
	status = nfsd4_process_open2(rqstp, resfh, open);
	WARN(status && open->op_created,
	     "nfsd4_process_open2 failed to open newly-created file! status=%u\n",
	     be32_to_cpu(status));
	if (reclaim && !status)
		nn->somebody_reclaimed = true;
out:
	if (resfh && resfh != &cstate->current_fh) {
		fh_dup2(&cstate->current_fh, resfh);
		fh_put(resfh);
		kfree(resfh);
	}
	nfsd4_cleanup_open_state(cstate, open);
	nfsd4_bump_seqid(cstate, status);
	return status;
}