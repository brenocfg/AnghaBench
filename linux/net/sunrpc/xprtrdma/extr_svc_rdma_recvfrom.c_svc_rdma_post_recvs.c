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
struct svcxprt_rdma {unsigned int sc_max_requests; } ;
struct svc_rdma_recv_ctxt {int rc_temp; } ;

/* Variables and functions */
 int __svc_rdma_post_recv (struct svcxprt_rdma*,struct svc_rdma_recv_ctxt*) ; 
 struct svc_rdma_recv_ctxt* svc_rdma_recv_ctxt_get (struct svcxprt_rdma*) ; 

bool svc_rdma_post_recvs(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_recv_ctxt *ctxt;
	unsigned int i;
	int ret;

	for (i = 0; i < rdma->sc_max_requests; i++) {
		ctxt = svc_rdma_recv_ctxt_get(rdma);
		if (!ctxt)
			return false;
		ctxt->rc_temp = true;
		ret = __svc_rdma_post_recv(rdma, ctxt);
		if (ret)
			return false;
	}
	return true;
}