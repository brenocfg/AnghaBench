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
struct svc_rdma_send_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  offset_in_page (unsigned char*) ; 
 int svc_rdma_dma_map_page (struct svcxprt_rdma*,struct svc_rdma_send_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  virt_to_page (unsigned char*) ; 

__attribute__((used)) static int svc_rdma_dma_map_buf(struct svcxprt_rdma *rdma,
				struct svc_rdma_send_ctxt *ctxt,
				unsigned char *base,
				unsigned int len)
{
	return svc_rdma_dma_map_page(rdma, ctxt, virt_to_page(base),
				     offset_in_page(base), len);
}