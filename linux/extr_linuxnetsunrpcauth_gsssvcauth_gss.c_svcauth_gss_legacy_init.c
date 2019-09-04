#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct kvec* head; } ;
struct TYPE_3__ {struct kvec* head; } ;
struct svc_rqst {int /*<<< orphan*/  rq_chandle; TYPE_2__ rq_res; TYPE_1__ rq_arg; } ;
struct sunrpc_net {int /*<<< orphan*/  rsi_cache; int /*<<< orphan*/  rsc_cache; } ;
struct rsi {int /*<<< orphan*/  h; int /*<<< orphan*/  minor_status; int /*<<< orphan*/  major_status; int /*<<< orphan*/  out_token; int /*<<< orphan*/  out_handle; int /*<<< orphan*/  in_token; int /*<<< orphan*/  in_handle; } ;
struct rpc_gss_wire_cred {int dummy; } ;
struct kvec {int dummy; } ;
typedef  int /*<<< orphan*/  rsikey ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SVC_CLOSE ; 
 int SVC_COMPLETE ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 scalar_t__ cache_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gss_read_verf (struct rpc_gss_wire_cred*,struct kvec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_write_init_verf (int /*<<< orphan*/ ,struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_write_resv (struct kvec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rsi*,int /*<<< orphan*/ ,int) ; 
 struct sunrpc_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_free (struct rsi*) ; 
 struct rsi* rsi_lookup (int /*<<< orphan*/ ,struct rsi*) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static int svcauth_gss_legacy_init(struct svc_rqst *rqstp,
			struct rpc_gss_wire_cred *gc, __be32 *authp)
{
	struct kvec *argv = &rqstp->rq_arg.head[0];
	struct kvec *resv = &rqstp->rq_res.head[0];
	struct rsi *rsip, rsikey;
	int ret;
	struct sunrpc_net *sn = net_generic(SVC_NET(rqstp), sunrpc_net_id);

	memset(&rsikey, 0, sizeof(rsikey));
	ret = gss_read_verf(gc, argv, authp,
			    &rsikey.in_handle, &rsikey.in_token);
	if (ret)
		return ret;

	/* Perform upcall, or find upcall result: */
	rsip = rsi_lookup(sn->rsi_cache, &rsikey);
	rsi_free(&rsikey);
	if (!rsip)
		return SVC_CLOSE;
	if (cache_check(sn->rsi_cache, &rsip->h, &rqstp->rq_chandle) < 0)
		/* No upcall result: */
		return SVC_CLOSE;

	ret = SVC_CLOSE;
	/* Got an answer to the upcall; use it: */
	if (gss_write_init_verf(sn->rsc_cache, rqstp,
				&rsip->out_handle, &rsip->major_status))
		goto out;
	if (gss_write_resv(resv, PAGE_SIZE,
			   &rsip->out_handle, &rsip->out_token,
			   rsip->major_status, rsip->minor_status))
		goto out;

	ret = SVC_COMPLETE;
out:
	cache_put(&rsip->h, sn->rsi_cache);
	return ret;
}