#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_6__ {int /*<<< orphan*/  mech; int /*<<< orphan*/  svc; int /*<<< orphan*/  qop; } ;
struct svc_rpc_gss_data {int win; int /*<<< orphan*/  ctx; TYPE_2__ sec; int /*<<< orphan*/  cname; int /*<<< orphan*/  client_name; int /*<<< orphan*/  seq; } ;
struct svc_req {TYPE_4__* rq_xprt; scalar_t__ rq_clntcred; } ;
struct TYPE_5__ {int length; int /*<<< orphan*/ * value; } ;
struct rpc_gss_init_res {scalar_t__ gr_major; scalar_t__ gr_minor; int gr_win; scalar_t__* value; int length; TYPE_1__ gr_ctx; int /*<<< orphan*/  gr_token; } ;
struct rpc_gss_cred {int /*<<< orphan*/  gc_seq; int /*<<< orphan*/  gc_svc; } ;
typedef  int /*<<< orphan*/  seq ;
typedef  int /*<<< orphan*/  recv_tok ;
typedef  int /*<<< orphan*/  gss_union_ctx_id_desc ;
typedef  struct rpc_gss_init_res gss_buffer_desc ;
typedef  int /*<<< orphan*/  gss_OID ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_7__ {scalar_t__* oa_base; int oa_length; int /*<<< orphan*/  oa_flavor; } ;
struct TYPE_8__ {TYPE_3__ xp_verf; int /*<<< orphan*/  xp_auth; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GSS_C_NO_CHANNEL_BINDINGS ; 
 int /*<<< orphan*/  GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  RPCSEC_GSS ; 
 struct svc_rpc_gss_data* SVCAUTH_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _svcauth_gss_creds ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gss_accept_sec_context (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rpc_gss_init_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_display_name (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_sign (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_gss_init_res*,struct rpc_gss_init_res*) ; 
 scalar_t__ htonl (int) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * mem_alloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct rpc_gss_init_res*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svc_getargs (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_rpc_gss_init_args ; 

__attribute__((used)) static bool_t
svcauth_gss_accept_sec_context(struct svc_req *rqst,
			       struct rpc_gss_init_res *gr)
{
	struct svc_rpc_gss_data	*gd;
	struct rpc_gss_cred	*gc;
	gss_buffer_desc		 recv_tok, seqbuf, checksum;
	gss_OID			 mech;
	OM_uint32		 maj_stat = 0, min_stat = 0, ret_flags, seq;

	log_debug("in svcauth_gss_accept_context()");

	gd = SVCAUTH_PRIVATE(rqst->rq_xprt->xp_auth);
	gc = (struct rpc_gss_cred *)rqst->rq_clntcred;
	memset(gr, 0, sizeof(*gr));

	/* Deserialize arguments. */
	memset(&recv_tok, 0, sizeof(recv_tok));

	if (!svc_getargs(rqst->rq_xprt, (xdrproc_t)xdr_rpc_gss_init_args,
			 (caddr_t)&recv_tok))
		return (FALSE);

	gr->gr_major = gss_accept_sec_context(&gr->gr_minor,
					      &gd->ctx,
					      _svcauth_gss_creds,
					      &recv_tok,
					      GSS_C_NO_CHANNEL_BINDINGS,
					      &gd->client_name,
					      &mech,
					      &gr->gr_token,
					      &ret_flags,
					      NULL,
					      NULL);

	if (gr->gr_major != GSS_S_COMPLETE &&
	    gr->gr_major != GSS_S_CONTINUE_NEEDED) {
		log_status("accept_sec_context", gr->gr_major, gr->gr_minor);
		gd->ctx = GSS_C_NO_CONTEXT;
		gss_release_buffer(&min_stat, &gr->gr_token);
		return (FALSE);
	}
	/* ANDROS: krb5 mechglue returns ctx of size 8 - two pointers,
	 * one to the mechanism oid, one to the internal_ctx_id */
	if ((gr->gr_ctx.value = mem_alloc(sizeof(gss_union_ctx_id_desc))) == NULL) {
		fprintf(stderr, "svcauth_gss_accept_context: out of memory\n");
		return (FALSE);
	}
	memcpy(gr->gr_ctx.value, gd->ctx, sizeof(gss_union_ctx_id_desc));
	gr->gr_ctx.length = sizeof(gss_union_ctx_id_desc);

	/* ANDROS: change for debugging linux kernel version...
	gr->gr_win = sizeof(gd->seqmask) * 8;
	*/
	gr->gr_win = 0x00000005;

	/* Save client info. */
	gd->sec.mech = mech;
	gd->sec.qop = GSS_C_QOP_DEFAULT;
	gd->sec.svc = gc->gc_svc;
	gd->seq = gc->gc_seq;
	gd->win = gr->gr_win;

	if (gr->gr_major == GSS_S_COMPLETE) {
		maj_stat = gss_display_name(&min_stat, gd->client_name,
					    &gd->cname, &gd->sec.mech);
		if (maj_stat != GSS_S_COMPLETE) {
			log_status("display_name", maj_stat, min_stat);
			return (FALSE);
		}
#ifdef DEBUG
#ifdef HAVE_KRB5
		{
			gss_buffer_desc mechname;

			gss_oid_to_str(&min_stat, mech, &mechname);

			log_debug("accepted context for %.*s with "
				  "<mech %.*s, qop %d, svc %d>",
				  gd->cname.length, (char *)gd->cname.value,
				  mechname.length, (char *)mechname.value,
				  gd->sec.qop, gd->sec.svc);

			gss_release_buffer(&min_stat, &mechname);
		}
#elif HAVE_HEIMDAL
		log_debug("accepted context for %.*s with "
			  "<mech {}, qop %d, svc %d>",
			  gd->cname.length, (char *)gd->cname.value,
			  gd->sec.qop, gd->sec.svc);
#endif
#endif /* DEBUG */
		seq = htonl(gr->gr_win);
		seqbuf.value = &seq;
		seqbuf.length = sizeof(seq);

		maj_stat = gss_sign(&min_stat, gd->ctx, GSS_C_QOP_DEFAULT,
				    &seqbuf, &checksum);

		if (maj_stat != GSS_S_COMPLETE)
			return (FALSE);

		rqst->rq_xprt->xp_verf.oa_flavor = RPCSEC_GSS;
		rqst->rq_xprt->xp_verf.oa_base = checksum.value;
		rqst->rq_xprt->xp_verf.oa_length = checksum.length;
	}
	return (TRUE);
}