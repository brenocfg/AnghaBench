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
struct xdr_netobj {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct rpc_gss_wire_cred {scalar_t__ gc_proc; TYPE_1__ gc_ctx; } ;
struct kvec {int iov_len; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_NULL ; 
 scalar_t__ RPC_GSS_PROC_INIT ; 
 int SVC_CLOSE ; 
 int SVC_DENIED ; 
 scalar_t__ dup_netobj (struct xdr_netobj*,TYPE_1__*) ; 
 int /*<<< orphan*/  rpc_autherr_badcred ; 
 int /*<<< orphan*/  rpc_autherr_badverf ; 
 scalar_t__ svc_getnl (struct kvec*) ; 

__attribute__((used)) static inline int
gss_read_common_verf(struct rpc_gss_wire_cred *gc,
		     struct kvec *argv, __be32 *authp,
		     struct xdr_netobj *in_handle)
{
	/* Read the verifier; should be NULL: */
	*authp = rpc_autherr_badverf;
	if (argv->iov_len < 2 * 4)
		return SVC_DENIED;
	if (svc_getnl(argv) != RPC_AUTH_NULL)
		return SVC_DENIED;
	if (svc_getnl(argv) != 0)
		return SVC_DENIED;
	/* Martial context handle and token for upcall: */
	*authp = rpc_autherr_badcred;
	if (gc->gc_proc == RPC_GSS_PROC_INIT && gc->gc_ctx.len != 0)
		return SVC_DENIED;
	if (dup_netobj(in_handle, &gc->gc_ctx))
		return SVC_CLOSE;
	*authp = rpc_autherr_badverf;

	return 0;
}