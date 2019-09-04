#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct xdr_netobj {int dummy; } ;
struct xdr_buf {int dummy; } ;
struct TYPE_2__ {struct kvec* head; } ;
struct svc_rqst {scalar_t__ rq_deferred; TYPE_1__ rq_arg; } ;
struct rsc {struct gss_ctx* mechctx; } ;
struct rpc_gss_wire_cred {scalar_t__ gc_seq; } ;
struct kvec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct gss_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ MAXSEQ ; 
 scalar_t__ RPC_AUTH_GSS ; 
 int SVC_DENIED ; 
 int SVC_DROP ; 
 int SVC_OK ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__) ; 
 int /*<<< orphan*/  gss_check_seq_num (struct rsc*,scalar_t__) ; 
 scalar_t__ gss_verify_mic (struct gss_ctx*,struct xdr_buf*,struct xdr_netobj*) ; 
 int /*<<< orphan*/  rpc_autherr_badverf ; 
 int /*<<< orphan*/  rpcsec_gsserr_credproblem ; 
 int /*<<< orphan*/  rpcsec_gsserr_ctxproblem ; 
 scalar_t__ svc_getnl (struct kvec*) ; 
 scalar_t__ svc_safe_getnetobj (struct kvec*,struct xdr_netobj*) ; 
 int /*<<< orphan*/  xdr_buf_from_iov (struct kvec*,struct xdr_buf*) ; 

__attribute__((used)) static int
gss_verify_header(struct svc_rqst *rqstp, struct rsc *rsci,
		  __be32 *rpcstart, struct rpc_gss_wire_cred *gc, __be32 *authp)
{
	struct gss_ctx		*ctx_id = rsci->mechctx;
	struct xdr_buf		rpchdr;
	struct xdr_netobj	checksum;
	u32			flavor = 0;
	struct kvec		*argv = &rqstp->rq_arg.head[0];
	struct kvec		iov;

	/* data to compute the checksum over: */
	iov.iov_base = rpcstart;
	iov.iov_len = (u8 *)argv->iov_base - (u8 *)rpcstart;
	xdr_buf_from_iov(&iov, &rpchdr);

	*authp = rpc_autherr_badverf;
	if (argv->iov_len < 4)
		return SVC_DENIED;
	flavor = svc_getnl(argv);
	if (flavor != RPC_AUTH_GSS)
		return SVC_DENIED;
	if (svc_safe_getnetobj(argv, &checksum))
		return SVC_DENIED;

	if (rqstp->rq_deferred) /* skip verification of revisited request */
		return SVC_OK;
	if (gss_verify_mic(ctx_id, &rpchdr, &checksum) != GSS_S_COMPLETE) {
		*authp = rpcsec_gsserr_credproblem;
		return SVC_DENIED;
	}

	if (gc->gc_seq > MAXSEQ) {
		dprintk("RPC:       svcauth_gss: discarding request with "
				"large sequence number %d\n", gc->gc_seq);
		*authp = rpcsec_gsserr_ctxproblem;
		return SVC_DENIED;
	}
	if (!gss_check_seq_num(rsci, gc->gc_seq)) {
		dprintk("RPC:       svcauth_gss: discarding request with "
				"old sequence number %d\n", gc->gc_seq);
		return SVC_DROP;
	}
	return SVC_OK;
}