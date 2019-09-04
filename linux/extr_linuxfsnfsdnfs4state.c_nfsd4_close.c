#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_close {int /*<<< orphan*/  cl_stateid; int /*<<< orphan*/  cl_seqid; } ;
union nfsd4_op_u {struct nfsd4_close close; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fh_dentry; } ;
struct nfsd4_compound_state {TYPE_1__ current_fh; } ;
struct TYPE_5__ {int sc_type; } ;
struct nfs4_ol_stateid {TYPE_2__ st_stid; int /*<<< orphan*/  st_mutex; } ;
struct net {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFS4_CLOSED_STID ; 
 int NFS4_OPEN_STID ; 
 struct net* SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  close_stateid ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_inc_and_copy_stateid (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ nfs4_preprocess_seqid_op (struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct nfs4_ol_stateid**,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfs4_put_stid (TYPE_2__*) ; 
 int /*<<< orphan*/  nfsd4_bump_seqid (struct nfsd4_compound_state*,scalar_t__) ; 
 int /*<<< orphan*/  nfsd4_close_open_stateid (struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

__be32
nfsd4_close(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	struct nfsd4_close *close = &u->close;
	__be32 status;
	struct nfs4_ol_stateid *stp;
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprintk("NFSD: nfsd4_close on file %pd\n", 
			cstate->current_fh.fh_dentry);

	status = nfs4_preprocess_seqid_op(cstate, close->cl_seqid,
					&close->cl_stateid,
					NFS4_OPEN_STID|NFS4_CLOSED_STID,
					&stp, nn);
	nfsd4_bump_seqid(cstate, status);
	if (status)
		goto out; 

	stp->st_stid.sc_type = NFS4_CLOSED_STID;

	/*
	 * Technically we don't _really_ have to increment or copy it, since
	 * it should just be gone after this operation and we clobber the
	 * copied value below, but we continue to do so here just to ensure
	 * that racing ops see that there was a state change.
	 */
	nfs4_inc_and_copy_stateid(&close->cl_stateid, &stp->st_stid);

	nfsd4_close_open_stateid(stp);
	mutex_unlock(&stp->st_mutex);

	/* v4.1+ suggests that we send a special stateid in here, since the
	 * clients should just ignore this anyway. Since this is not useful
	 * for v4.0 clients either, we set it to the special close_stateid
	 * universally.
	 *
	 * See RFC5661 section 18.2.4, and RFC7530 section 16.2.5
	 */
	memcpy(&close->cl_stateid, &close_stateid, sizeof(close->cl_stateid));

	/* put reference from nfs4_preprocess_seqid_op */
	nfs4_put_stid(&stp->st_stid);
out:
	return status;
}