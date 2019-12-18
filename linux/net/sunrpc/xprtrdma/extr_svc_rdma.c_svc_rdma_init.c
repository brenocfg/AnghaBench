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

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ register_sysctl_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_class ; 
 int /*<<< orphan*/  svc_reg_xprt_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcrdma_max_bc_requests ; 
 int /*<<< orphan*/  svcrdma_max_req_size ; 
 int /*<<< orphan*/  svcrdma_max_requests ; 
 int /*<<< orphan*/  svcrdma_ord ; 
 int /*<<< orphan*/  svcrdma_root_table ; 
 scalar_t__ svcrdma_table_header ; 

int svc_rdma_init(void)
{
	dprintk("SVCRDMA Module Init, register RPC RDMA transport\n");
	dprintk("\tsvcrdma_ord      : %d\n", svcrdma_ord);
	dprintk("\tmax_requests     : %u\n", svcrdma_max_requests);
	dprintk("\tmax_bc_requests  : %u\n", svcrdma_max_bc_requests);
	dprintk("\tmax_inline       : %d\n", svcrdma_max_req_size);

	if (!svcrdma_table_header)
		svcrdma_table_header =
			register_sysctl_table(svcrdma_root_table);

	/* Register RDMA with the SVC transport switch */
	svc_reg_xprt_class(&svc_rdma_class);
	return 0;
}