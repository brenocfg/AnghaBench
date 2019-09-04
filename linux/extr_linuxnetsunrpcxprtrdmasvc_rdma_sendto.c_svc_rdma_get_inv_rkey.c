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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpup (scalar_t__*) ; 
 int rpcrdma_fixed_maxsz ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static u32 svc_rdma_get_inv_rkey(__be32 *rdma_argp,
				 __be32 *wr_lst, __be32 *rp_ch)
{
	__be32 *p;

	p = rdma_argp + rpcrdma_fixed_maxsz;
	if (*p != xdr_zero)
		p += 2;
	else if (wr_lst && be32_to_cpup(wr_lst + 1))
		p = wr_lst + 2;
	else if (rp_ch && be32_to_cpup(rp_ch + 1))
		p = rp_ch + 2;
	else
		return 0;
	return be32_to_cpup(p);
}