#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct svc_rpc_gss_data {int seqlast; int seqmask; int win; int seq; void* established; scalar_t__ ctx; scalar_t__ client_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  oa_length; int /*<<< orphan*/  oa_base; } ;
struct svc_req {char* rq_clntname; char* rq_svcname; TYPE_3__* rq_xprt; int /*<<< orphan*/  rq_proc; TYPE_1__ rq_cred; scalar_t__ rq_clntcred; } ;
struct rpc_msg {int dummy; } ;
struct rpc_gss_init_res {int gr_win; int /*<<< orphan*/  gr_major; } ;
struct rpc_gss_cred {scalar_t__ gc_v; scalar_t__ gc_svc; scalar_t__ gc_seq; int gc_proc; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;
typedef  scalar_t__ caddr_t ;
typedef  int bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_9__ {TYPE_2__* xp_auth; int /*<<< orphan*/  xp_verf; } ;
struct TYPE_8__ {scalar_t__ svc_ah_private; int /*<<< orphan*/ * svc_ah_ops; } ;
typedef  TYPE_2__ SVCAUTH ;

/* Variables and functions */
 int AUTH_BADCRED ; 
 int AUTH_FAILED ; 
 int AUTH_OK ; 
 int AUTH_REJECTEDCRED ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 scalar_t__ MAXSEQ ; 
 int /*<<< orphan*/  NULLPROC ; 
#define  RPCSEC_GSS_CONTINUE_INIT 131 
 int RPCSEC_GSS_CREDPROBLEM ; 
 int RPCSEC_GSS_CTXPROBLEM ; 
#define  RPCSEC_GSS_DATA 130 
#define  RPCSEC_GSS_DESTROY 129 
#define  RPCSEC_GSS_INIT 128 
 scalar_t__ RPCSEC_GSS_SVC_INTEGRITY ; 
 scalar_t__ RPCSEC_GSS_SVC_NONE ; 
 scalar_t__ RPCSEC_GSS_SVC_PRIVACY ; 
 scalar_t__ RPCSEC_GSS_VERSION ; 
 int /*<<< orphan*/  SVCAUTH_DESTROY (TYPE_2__*) ; 
 struct svc_rpc_gss_data* SVCAUTH_PRIVATE (TYPE_2__*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _null_auth ; 
 int /*<<< orphan*/ * _svcauth_gss_name ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  memset (struct rpc_gss_cred*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svc_auth_gss_ops ; 
 TYPE_2__ svc_auth_none ; 
 int svc_sendreply (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svcauth_gss_accept_sec_context (struct svc_req*,struct rpc_gss_init_res*) ; 
 int /*<<< orphan*/  svcauth_gss_acquire_cred () ; 
 int /*<<< orphan*/  svcauth_gss_import_name (char*) ; 
 int /*<<< orphan*/  svcauth_gss_nextverf (struct svc_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcauth_gss_release_cred () ; 
 int /*<<< orphan*/  svcauth_gss_validate (struct svc_rpc_gss_data*,struct rpc_msg*) ; 
 int /*<<< orphan*/  xdr_rpc_gss_cred (int /*<<< orphan*/ *,struct rpc_gss_cred*) ; 
 int /*<<< orphan*/  xdr_rpc_gss_init_res ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum auth_stat
_svcauth_gss(struct svc_req *rqst, struct rpc_msg *msg, bool_t *no_dispatch)
{
	XDR	 		 xdrs;
	SVCAUTH			*auth;
	struct svc_rpc_gss_data	*gd;
	struct rpc_gss_cred	*gc;
	struct rpc_gss_init_res	 gr;
	int			 call_stat, offset;

	log_debug("in svcauth_gss()");

	/* Initialize reply. */
	rqst->rq_xprt->xp_verf = _null_auth;

	/* Allocate and set up server auth handle. */
	if (rqst->rq_xprt->xp_auth == NULL ||
	    rqst->rq_xprt->xp_auth == &svc_auth_none) {
		if ((auth = calloc(sizeof(*auth), 1)) == NULL) {
			fprintf(stderr, "svcauth_gss: out_of_memory\n");
			return (AUTH_FAILED);
		}
		if ((gd = calloc(sizeof(*gd), 1)) == NULL) {
			fprintf(stderr, "svcauth_gss: out_of_memory\n");
			return (AUTH_FAILED);
		}
		auth->svc_ah_ops = &svc_auth_gss_ops;
		auth->svc_ah_private = (caddr_t) gd;
		rqst->rq_xprt->xp_auth = auth;
	}
	else gd = SVCAUTH_PRIVATE(rqst->rq_xprt->xp_auth);

	/* Deserialize client credentials. */
	if (rqst->rq_cred.oa_length <= 0)
		return (AUTH_BADCRED);

	gc = (struct rpc_gss_cred *)rqst->rq_clntcred;
	memset(gc, 0, sizeof(*gc));

	xdrmem_create(&xdrs, rqst->rq_cred.oa_base,
		      rqst->rq_cred.oa_length, XDR_DECODE);

	if (!xdr_rpc_gss_cred(&xdrs, gc)) {
		XDR_DESTROY(&xdrs);
		return (AUTH_BADCRED);
	}
	XDR_DESTROY(&xdrs);

	/* Check version. */
	if (gc->gc_v != RPCSEC_GSS_VERSION)
		return (AUTH_BADCRED);

	/* Check RPCSEC_GSS service. */
	if (gc->gc_svc != RPCSEC_GSS_SVC_NONE &&
	    gc->gc_svc != RPCSEC_GSS_SVC_INTEGRITY &&
	    gc->gc_svc != RPCSEC_GSS_SVC_PRIVACY)
		return (AUTH_BADCRED);

	/* Check sequence number. */
	if (gd->established) {
		if (gc->gc_seq > MAXSEQ)
			return (RPCSEC_GSS_CTXPROBLEM);

		if ((offset = gd->seqlast - gc->gc_seq) < 0) {
			gd->seqlast = gc->gc_seq;
			offset = 0 - offset;
			gd->seqmask <<= offset;
			offset = 0;
		}
		else if (offset >= gd->win || (gd->seqmask & (1 << offset))) {
			*no_dispatch = 1;
			return (RPCSEC_GSS_CTXPROBLEM);
		}
		gd->seq = gc->gc_seq;
		gd->seqmask |= (1 << offset);
	}

	if (gd->established) {
		rqst->rq_clntname = (char *)gd->client_name;
		rqst->rq_svcname = (char *)gd->ctx;
	}

	/* Handle RPCSEC_GSS control procedure. */
	switch (gc->gc_proc) {

	case RPCSEC_GSS_INIT:
	case RPCSEC_GSS_CONTINUE_INIT:
		if (rqst->rq_proc != NULLPROC)
			return (AUTH_FAILED);		/* XXX ? */

		if (_svcauth_gss_name == NULL) {
			if (!svcauth_gss_import_name("nfs"))
				return (AUTH_FAILED);
		}

		if (!svcauth_gss_acquire_cred())
			return (AUTH_FAILED);

		if (!svcauth_gss_accept_sec_context(rqst, &gr))
			return (AUTH_REJECTEDCRED);

		if (!svcauth_gss_nextverf(rqst, htonl(gr.gr_win)))
			return (AUTH_FAILED);

		*no_dispatch = TRUE;

		call_stat = svc_sendreply(rqst->rq_xprt, 
			(xdrproc_t)xdr_rpc_gss_init_res, (caddr_t)&gr);

		if (!call_stat)
			return (AUTH_FAILED);

		if (gr.gr_major == GSS_S_COMPLETE)
			gd->established = TRUE;

		break;

	case RPCSEC_GSS_DATA:
		if (!svcauth_gss_validate(gd, msg))
			return (RPCSEC_GSS_CREDPROBLEM);

		if (!svcauth_gss_nextverf(rqst, htonl(gc->gc_seq)))
			return (AUTH_FAILED);
		break;

	case RPCSEC_GSS_DESTROY:
		if (rqst->rq_proc != NULLPROC)
			return (AUTH_FAILED);		/* XXX ? */

		if (!svcauth_gss_validate(gd, msg))
			return (RPCSEC_GSS_CREDPROBLEM);

		if (!svcauth_gss_nextverf(rqst, htonl(gc->gc_seq)))
			return (AUTH_FAILED);

		if (!svcauth_gss_release_cred())
			return (AUTH_FAILED);

		SVCAUTH_DESTROY(rqst->rq_xprt->xp_auth);
		rqst->rq_xprt->xp_auth = &svc_auth_none;

		break;

	default:
		return (AUTH_REJECTEDCRED);
		break;
	}
	return (AUTH_OK);
}