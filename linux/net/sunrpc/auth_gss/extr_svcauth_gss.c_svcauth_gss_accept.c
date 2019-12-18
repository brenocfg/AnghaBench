#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_11__ {int /*<<< orphan*/  cr_flavor; int /*<<< orphan*/  cr_group_info; } ;
struct TYPE_12__ {struct kvec* head; } ;
struct TYPE_10__ {struct kvec* head; } ;
struct svc_rqst {scalar_t__ rq_proc; int rq_auth_slack; TYPE_2__ rq_cred; TYPE_3__ rq_arg; struct gss_svc_data* rq_auth_data; TYPE_1__ rq_res; } ;
struct sunrpc_net {int /*<<< orphan*/  rsc_cache; } ;
struct rsc {int /*<<< orphan*/  h; TYPE_4__* mechctx; TYPE_2__ cred; } ;
struct TYPE_14__ {int /*<<< orphan*/  len; } ;
struct rpc_gss_wire_cred {int gc_proc; scalar_t__ gc_svc; scalar_t__ gc_seq; TYPE_7__ gc_ctx; } ;
struct kvec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct gss_svc_data {struct rsc* rsci; int /*<<< orphan*/ * verf_start; struct rpc_gss_wire_cred clcred; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_13__ {int /*<<< orphan*/  mech_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int PAGE_SIZE ; 
#define  RPC_GSS_PROC_CONTINUE_INIT 137 
#define  RPC_GSS_PROC_DATA 136 
#define  RPC_GSS_PROC_DESTROY 135 
#define  RPC_GSS_PROC_INIT 134 
#define  RPC_GSS_SVC_INTEGRITY 133 
#define  RPC_GSS_SVC_NONE 132 
#define  RPC_GSS_SVC_PRIVACY 131 
 scalar_t__ RPC_GSS_VERSION ; 
 int RPC_MAX_AUTH_SIZE ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int SVC_CLOSE ; 
 int SVC_COMPLETE ; 
#define  SVC_DENIED 130 
#define  SVC_DROP 129 
 int SVC_GARBAGE ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
#define  SVC_OK 128 
 int /*<<< orphan*/  cache_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ ) ; 
 struct rsc* gss_svc_searchbyctx (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  gss_svc_to_pseudoflavor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gss_verify_header (struct svc_rqst*,struct rsc*,int /*<<< orphan*/ *,struct rpc_gss_wire_cred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_write_verf (struct svc_rqst*,TYPE_4__*,scalar_t__) ; 
 struct gss_svc_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct sunrpc_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ round_up_to_quad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_autherr_badcred ; 
 int /*<<< orphan*/  rpc_autherr_badverf ; 
 int /*<<< orphan*/  rpc_autherr_rejectedcred ; 
 int /*<<< orphan*/  rpcsec_gsserr_credproblem ; 
 int /*<<< orphan*/  rpcsec_gsserr_ctxproblem ; 
 int /*<<< orphan*/  sunrpc_cache_unhash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 
 scalar_t__ svc_getnl (struct kvec*) ; 
 int /*<<< orphan*/  svc_putnl (struct kvec*,int /*<<< orphan*/ ) ; 
 scalar_t__ svc_safe_getnetobj (struct kvec*,TYPE_7__*) ; 
 int svcauth_gss_legacy_init (struct svc_rqst*,struct rpc_gss_wire_cred*,int /*<<< orphan*/ *) ; 
 int svcauth_gss_proxy_init (struct svc_rqst*,struct rpc_gss_wire_cred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unwrap_integ_data (struct svc_rqst*,TYPE_3__*,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  unwrap_priv_data (struct svc_rqst*,TYPE_3__*,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  use_gss_proxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
svcauth_gss_accept(struct svc_rqst *rqstp, __be32 *authp)
{
	struct kvec	*argv = &rqstp->rq_arg.head[0];
	struct kvec	*resv = &rqstp->rq_res.head[0];
	u32		crlen;
	struct gss_svc_data *svcdata = rqstp->rq_auth_data;
	struct rpc_gss_wire_cred *gc;
	struct rsc	*rsci = NULL;
	__be32		*rpcstart;
	__be32		*reject_stat = resv->iov_base + resv->iov_len;
	int		ret;
	struct sunrpc_net *sn = net_generic(SVC_NET(rqstp), sunrpc_net_id);

	dprintk("RPC:       svcauth_gss: argv->iov_len = %zd\n",
			argv->iov_len);

	*authp = rpc_autherr_badcred;
	if (!svcdata)
		svcdata = kmalloc(sizeof(*svcdata), GFP_KERNEL);
	if (!svcdata)
		goto auth_err;
	rqstp->rq_auth_data = svcdata;
	svcdata->verf_start = NULL;
	svcdata->rsci = NULL;
	gc = &svcdata->clcred;

	/* start of rpc packet is 7 u32's back from here:
	 * xid direction rpcversion prog vers proc flavour
	 */
	rpcstart = argv->iov_base;
	rpcstart -= 7;

	/* credential is:
	 *   version(==1), proc(0,1,2,3), seq, service (1,2,3), handle
	 * at least 5 u32s, and is preceded by length, so that makes 6.
	 */

	if (argv->iov_len < 5 * 4)
		goto auth_err;
	crlen = svc_getnl(argv);
	if (svc_getnl(argv) != RPC_GSS_VERSION)
		goto auth_err;
	gc->gc_proc = svc_getnl(argv);
	gc->gc_seq = svc_getnl(argv);
	gc->gc_svc = svc_getnl(argv);
	if (svc_safe_getnetobj(argv, &gc->gc_ctx))
		goto auth_err;
	if (crlen != round_up_to_quad(gc->gc_ctx.len) + 5 * 4)
		goto auth_err;

	if ((gc->gc_proc != RPC_GSS_PROC_DATA) && (rqstp->rq_proc != 0))
		goto auth_err;

	*authp = rpc_autherr_badverf;
	switch (gc->gc_proc) {
	case RPC_GSS_PROC_INIT:
	case RPC_GSS_PROC_CONTINUE_INIT:
		if (use_gss_proxy(SVC_NET(rqstp)))
			return svcauth_gss_proxy_init(rqstp, gc, authp);
		else
			return svcauth_gss_legacy_init(rqstp, gc, authp);
	case RPC_GSS_PROC_DATA:
	case RPC_GSS_PROC_DESTROY:
		/* Look up the context, and check the verifier: */
		*authp = rpcsec_gsserr_credproblem;
		rsci = gss_svc_searchbyctx(sn->rsc_cache, &gc->gc_ctx);
		if (!rsci)
			goto auth_err;
		switch (gss_verify_header(rqstp, rsci, rpcstart, gc, authp)) {
		case SVC_OK:
			break;
		case SVC_DENIED:
			goto auth_err;
		case SVC_DROP:
			goto drop;
		}
		break;
	default:
		*authp = rpc_autherr_rejectedcred;
		goto auth_err;
	}

	/* now act upon the command: */
	switch (gc->gc_proc) {
	case RPC_GSS_PROC_DESTROY:
		if (gss_write_verf(rqstp, rsci->mechctx, gc->gc_seq))
			goto auth_err;
		/* Delete the entry from the cache_list and call cache_put */
		sunrpc_cache_unhash(sn->rsc_cache, &rsci->h);
		if (resv->iov_len + 4 > PAGE_SIZE)
			goto drop;
		svc_putnl(resv, RPC_SUCCESS);
		goto complete;
	case RPC_GSS_PROC_DATA:
		*authp = rpcsec_gsserr_ctxproblem;
		svcdata->verf_start = resv->iov_base + resv->iov_len;
		if (gss_write_verf(rqstp, rsci->mechctx, gc->gc_seq))
			goto auth_err;
		rqstp->rq_cred = rsci->cred;
		get_group_info(rsci->cred.cr_group_info);
		*authp = rpc_autherr_badcred;
		switch (gc->gc_svc) {
		case RPC_GSS_SVC_NONE:
			break;
		case RPC_GSS_SVC_INTEGRITY:
			/* placeholders for length and seq. number: */
			svc_putnl(resv, 0);
			svc_putnl(resv, 0);
			if (unwrap_integ_data(rqstp, &rqstp->rq_arg,
					gc->gc_seq, rsci->mechctx))
				goto garbage_args;
			rqstp->rq_auth_slack = RPC_MAX_AUTH_SIZE;
			break;
		case RPC_GSS_SVC_PRIVACY:
			/* placeholders for length and seq. number: */
			svc_putnl(resv, 0);
			svc_putnl(resv, 0);
			if (unwrap_priv_data(rqstp, &rqstp->rq_arg,
					gc->gc_seq, rsci->mechctx))
				goto garbage_args;
			rqstp->rq_auth_slack = RPC_MAX_AUTH_SIZE * 2;
			break;
		default:
			goto auth_err;
		}
		svcdata->rsci = rsci;
		cache_get(&rsci->h);
		rqstp->rq_cred.cr_flavor = gss_svc_to_pseudoflavor(
					rsci->mechctx->mech_type,
					GSS_C_QOP_DEFAULT,
					gc->gc_svc);
		ret = SVC_OK;
		goto out;
	}
garbage_args:
	ret = SVC_GARBAGE;
	goto out;
auth_err:
	/* Restore write pointer to its original value: */
	xdr_ressize_check(rqstp, reject_stat);
	ret = SVC_DENIED;
	goto out;
complete:
	ret = SVC_COMPLETE;
	goto out;
drop:
	ret = SVC_CLOSE;
out:
	if (rsci)
		cache_put(&rsci->h, sn->rsc_cache);
	return ret;
}