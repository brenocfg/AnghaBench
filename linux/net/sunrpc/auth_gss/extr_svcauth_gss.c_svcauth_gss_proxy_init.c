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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ud ;
typedef  int /*<<< orphan*/  u8 ;
struct xdr_netobj {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {struct kvec* head; } ;
struct svc_rqst {TYPE_1__ rq_res; } ;
struct sunrpc_net {int /*<<< orphan*/  rsc_cache; } ;
struct rpc_gss_wire_cred {int dummy; } ;
struct net {int dummy; } ;
struct kvec {int dummy; } ;
struct gssp_upcall_data {int major_status; int /*<<< orphan*/  minor_status; int /*<<< orphan*/  out_token; struct xdr_netobj out_handle; int /*<<< orphan*/  in_token; int /*<<< orphan*/  in_handle; } ;
typedef  int /*<<< orphan*/  handle ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  GSS_S_COMPLETE 129 
#define  GSS_S_CONTINUE_NEEDED 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SVC_CLOSE ; 
 int SVC_COMPLETE ; 
 struct net* SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 
 int gss_proxy_save_rsc (int /*<<< orphan*/ ,struct gssp_upcall_data*,int /*<<< orphan*/ *) ; 
 int gss_read_proxy_verf (struct svc_rqst*,struct rpc_gss_wire_cred*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_write_init_verf (int /*<<< orphan*/ ,struct svc_rqst*,struct xdr_netobj*,int*) ; 
 scalar_t__ gss_write_resv (struct kvec*,int /*<<< orphan*/ ,struct xdr_netobj*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int gssp_accept_sec_context_upcall (struct net*,struct gssp_upcall_data*) ; 
 int /*<<< orphan*/  gssp_free_upcall_data (struct gssp_upcall_data*) ; 
 int /*<<< orphan*/  memset (struct gssp_upcall_data*,int /*<<< orphan*/ ,int) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static int svcauth_gss_proxy_init(struct svc_rqst *rqstp,
			struct rpc_gss_wire_cred *gc, __be32 *authp)
{
	struct kvec *resv = &rqstp->rq_res.head[0];
	struct xdr_netobj cli_handle;
	struct gssp_upcall_data ud;
	uint64_t handle;
	int status;
	int ret;
	struct net *net = SVC_NET(rqstp);
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	memset(&ud, 0, sizeof(ud));
	ret = gss_read_proxy_verf(rqstp, gc, authp,
				  &ud.in_handle, &ud.in_token);
	if (ret)
		return ret;

	ret = SVC_CLOSE;

	/* Perform synchronous upcall to gss-proxy */
	status = gssp_accept_sec_context_upcall(net, &ud);
	if (status)
		goto out;

	dprintk("RPC:       svcauth_gss: gss major status = %d "
			"minor status = %d\n",
			ud.major_status, ud.minor_status);

	switch (ud.major_status) {
	case GSS_S_CONTINUE_NEEDED:
		cli_handle = ud.out_handle;
		break;
	case GSS_S_COMPLETE:
		status = gss_proxy_save_rsc(sn->rsc_cache, &ud, &handle);
		if (status)
			goto out;
		cli_handle.data = (u8 *)&handle;
		cli_handle.len = sizeof(handle);
		break;
	default:
		ret = SVC_CLOSE;
		goto out;
	}

	/* Got an answer to the upcall; use it: */
	if (gss_write_init_verf(sn->rsc_cache, rqstp,
				&cli_handle, &ud.major_status))
		goto out;
	if (gss_write_resv(resv, PAGE_SIZE,
			   &cli_handle, &ud.out_token,
			   ud.major_status, ud.minor_status))
		goto out;

	ret = SVC_COMPLETE;
out:
	gssp_free_upcall_data(&ud);
	return ret;
}