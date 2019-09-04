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
struct svcxprt_rdma {int dummy; } ;
struct svc_rdma_recv_ctxt {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __svc_rdma_post_recv (struct svcxprt_rdma*,struct svc_rdma_recv_ctxt*) ; 
 struct svc_rdma_recv_ctxt* svc_rdma_recv_ctxt_get (struct svcxprt_rdma*) ; 

__attribute__((used)) static int svc_rdma_post_recv(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_recv_ctxt *ctxt;

	ctxt = svc_rdma_recv_ctxt_get(rdma);
	if (!ctxt)
		return -ENOMEM;
	return __svc_rdma_post_recv(rdma, ctxt);
}