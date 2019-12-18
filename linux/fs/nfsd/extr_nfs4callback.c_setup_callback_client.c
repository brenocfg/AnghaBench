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
struct sockaddr {int dummy; } ;
struct rpc_timeout {int to_initval; int to_maxval; int /*<<< orphan*/  to_retries; } ;
struct rpc_create_args {int version; int flags; int protocol; scalar_t__ authflavor; int /*<<< orphan*/  prognumber; TYPE_4__* bc_xprt; scalar_t__ client_name; int /*<<< orphan*/  cred; int /*<<< orphan*/ * program; struct rpc_timeout* timeout; struct sockaddr* saddress; int /*<<< orphan*/  addrsize; struct sockaddr* address; int /*<<< orphan*/  net; } ;
struct rpc_clnt {int dummy; } ;
struct TYPE_10__ {scalar_t__ flavor; } ;
struct nfsd4_session {TYPE_5__ se_cb_sec; int /*<<< orphan*/  se_cb_prog; } ;
struct TYPE_7__ {TYPE_4__* cb_xprt; } ;
struct TYPE_6__ {scalar_t__ cr_flavor; scalar_t__ cr_principal; } ;
struct nfs4_client {scalar_t__ cl_minorversion; struct cred const* cl_cb_cred; struct rpc_clnt* cl_cb_client; struct nfsd4_session* cl_cb_session; TYPE_2__ cl_cb_conn; int /*<<< orphan*/  cl_cb_ident; TYPE_1__ cl_cred; int /*<<< orphan*/  net; } ;
struct nfs4_cb_conn {TYPE_4__* cb_xprt; int /*<<< orphan*/  cb_ident; int /*<<< orphan*/  cb_prog; int /*<<< orphan*/  cb_saddr; int /*<<< orphan*/  cb_addrlen; int /*<<< orphan*/  cb_addr; } ;
struct cred {int dummy; } ;
struct TYPE_9__ {TYPE_3__* xpt_class; } ;
struct TYPE_8__ {int xcl_ident; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct rpc_clnt*) ; 
 int PTR_ERR (struct rpc_clnt*) ; 
 scalar_t__ RPC_AUTH_GSS_KRB5 ; 
 int RPC_CLNT_CREATE_NOPING ; 
 int RPC_CLNT_CREATE_QUIET ; 
 int XPRT_TRANSPORT_BC ; 
 int XPRT_TRANSPORT_TCP ; 
 int /*<<< orphan*/  cb_program ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 struct cred* get_backchannel_cred (struct nfs4_client*,struct rpc_clnt*,struct nfsd4_session*) ; 
 int max_cb_time (int /*<<< orphan*/ ) ; 
 struct rpc_clnt* rpc_create (struct rpc_create_args*) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 

__attribute__((used)) static int setup_callback_client(struct nfs4_client *clp, struct nfs4_cb_conn *conn, struct nfsd4_session *ses)
{
	int maxtime = max_cb_time(clp->net);
	struct rpc_timeout	timeparms = {
		.to_initval	= maxtime,
		.to_retries	= 0,
		.to_maxval	= maxtime,
	};
	struct rpc_create_args args = {
		.net		= clp->net,
		.address	= (struct sockaddr *) &conn->cb_addr,
		.addrsize	= conn->cb_addrlen,
		.saddress	= (struct sockaddr *) &conn->cb_saddr,
		.timeout	= &timeparms,
		.program	= &cb_program,
		.version	= 1,
		.flags		= (RPC_CLNT_CREATE_NOPING | RPC_CLNT_CREATE_QUIET),
		.cred		= current_cred(),
	};
	struct rpc_clnt *client;
	const struct cred *cred;

	if (clp->cl_minorversion == 0) {
		if (!clp->cl_cred.cr_principal &&
				(clp->cl_cred.cr_flavor >= RPC_AUTH_GSS_KRB5))
			return -EINVAL;
		args.client_name = clp->cl_cred.cr_principal;
		args.prognumber	= conn->cb_prog;
		args.protocol = XPRT_TRANSPORT_TCP;
		args.authflavor = clp->cl_cred.cr_flavor;
		clp->cl_cb_ident = conn->cb_ident;
	} else {
		if (!conn->cb_xprt)
			return -EINVAL;
		clp->cl_cb_conn.cb_xprt = conn->cb_xprt;
		clp->cl_cb_session = ses;
		args.bc_xprt = conn->cb_xprt;
		args.prognumber = clp->cl_cb_session->se_cb_prog;
		args.protocol = conn->cb_xprt->xpt_class->xcl_ident |
				XPRT_TRANSPORT_BC;
		args.authflavor = ses->se_cb_sec.flavor;
	}
	/* Create RPC client */
	client = rpc_create(&args);
	if (IS_ERR(client)) {
		dprintk("NFSD: couldn't create callback client: %ld\n",
			PTR_ERR(client));
		return PTR_ERR(client);
	}
	cred = get_backchannel_cred(clp, client, ses);
	if (!cred) {
		rpc_shutdown_client(client);
		return -ENOMEM;
	}
	clp->cl_cb_client = client;
	clp->cl_cb_cred = cred;
	return 0;
}