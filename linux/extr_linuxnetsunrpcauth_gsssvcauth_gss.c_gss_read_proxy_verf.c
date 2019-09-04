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
typedef  int ulong ;
typedef  scalar_t__ u32 ;
struct xdr_netobj {int dummy; } ;
struct TYPE_2__ {scalar_t__ page_len; struct kvec* head; } ;
struct svc_rqst {int /*<<< orphan*/  rq_pages; TYPE_1__ rq_arg; } ;
struct rpc_gss_wire_cred {int dummy; } ;
struct kvec {scalar_t__ iov_len; scalar_t__ iov_base; } ;
struct gssp_in_token {int page_base; scalar_t__ page_len; int /*<<< orphan*/  pages; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int PAGE_MASK ; 
 int SVC_DENIED ; 
 int gss_read_common_verf (struct rpc_gss_wire_cred*,struct kvec*,int /*<<< orphan*/ *,struct xdr_netobj*) ; 
 scalar_t__ svc_getnl (struct kvec*) ; 

__attribute__((used)) static inline int
gss_read_proxy_verf(struct svc_rqst *rqstp,
		    struct rpc_gss_wire_cred *gc, __be32 *authp,
		    struct xdr_netobj *in_handle,
		    struct gssp_in_token *in_token)
{
	struct kvec *argv = &rqstp->rq_arg.head[0];
	u32 inlen;
	int res;

	res = gss_read_common_verf(gc, argv, authp, in_handle);
	if (res)
		return res;

	inlen = svc_getnl(argv);
	if (inlen > (argv->iov_len + rqstp->rq_arg.page_len))
		return SVC_DENIED;

	in_token->pages = rqstp->rq_pages;
	in_token->page_base = (ulong)argv->iov_base & ~PAGE_MASK;
	in_token->page_len = inlen;

	return 0;
}