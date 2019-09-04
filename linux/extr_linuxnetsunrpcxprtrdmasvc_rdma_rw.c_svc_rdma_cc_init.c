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
struct svcxprt_rdma {int /*<<< orphan*/  sc_xprt; } ;
struct svc_rdma_chunk_ctxt {scalar_t__ cc_sqecount; int /*<<< orphan*/  cc_rwctxts; struct svcxprt_rdma* cc_rdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void svc_rdma_cc_init(struct svcxprt_rdma *rdma,
			     struct svc_rdma_chunk_ctxt *cc)
{
	cc->cc_rdma = rdma;
	svc_xprt_get(&rdma->sc_xprt);

	INIT_LIST_HEAD(&cc->cc_rwctxts);
	cc->cc_sqecount = 0;
}