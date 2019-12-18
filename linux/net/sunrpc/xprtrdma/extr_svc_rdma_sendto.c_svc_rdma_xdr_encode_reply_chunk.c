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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int rpcrdma_fixed_maxsz ; 
 int rpcrdma_segment_maxsz ; 
 int /*<<< orphan*/  xdr_encode_write_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static void svc_rdma_xdr_encode_reply_chunk(__be32 *rdma_resp, __be32 *rp_ch,
					    unsigned int consumed)
{
	__be32 *p;

	/* Find the Reply chunk in the Reply's xprt header.
	 * RPC-over-RDMA V1 replies never have a Read list.
	 */
	p = rdma_resp + rpcrdma_fixed_maxsz + 1;

	/* Skip past Write list */
	while (*p++ != xdr_zero)
		p += 1 + be32_to_cpup(p) * rpcrdma_segment_maxsz;

	xdr_encode_write_chunk(p, rp_ch, consumed);
}