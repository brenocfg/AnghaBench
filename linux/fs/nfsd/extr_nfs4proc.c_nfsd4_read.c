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
struct nfsd4_read {scalar_t__ rd_offset; int /*<<< orphan*/ * rd_fhp; struct svc_rqst* rd_rqstp; int /*<<< orphan*/ * rd_nf; int /*<<< orphan*/  rd_stateid; int /*<<< orphan*/  rd_length; } ;
union nfsd4_op_u {struct nfsd4_read read; } ;
struct svc_rqst {int /*<<< orphan*/  rq_flags; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ OFFSET_MAX ; 
 int /*<<< orphan*/  RD_STATE ; 
 int /*<<< orphan*/  RQ_SPLICE_OK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ nfs4_preprocess_stateid_op (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_last_compound_op (struct svc_rqst*) ; 
 scalar_t__ nfserr_inval ; 
 int /*<<< orphan*/  trace_nfsd_read_start (struct svc_rqst*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_read(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	   union nfsd4_op_u *u)
{
	struct nfsd4_read *read = &u->read;
	__be32 status;

	read->rd_nf = NULL;
	if (read->rd_offset >= OFFSET_MAX)
		return nfserr_inval;

	trace_nfsd_read_start(rqstp, &cstate->current_fh,
			      read->rd_offset, read->rd_length);

	/*
	 * If we do a zero copy read, then a client will see read data
	 * that reflects the state of the file *after* performing the
	 * following compound.
	 *
	 * To ensure proper ordering, we therefore turn off zero copy if
	 * the client wants us to do more in this compound:
	 */
	if (!nfsd4_last_compound_op(rqstp))
		clear_bit(RQ_SPLICE_OK, &rqstp->rq_flags);

	/* check stateid */
	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
					&read->rd_stateid, RD_STATE,
					&read->rd_nf);
	if (status) {
		dprintk("NFSD: nfsd4_read: couldn't process stateid!\n");
		goto out;
	}
	status = nfs_ok;
out:
	read->rd_rqstp = rqstp;
	read->rd_fhp = &cstate->current_fh;
	return status;
}