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
 unsigned int be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ rpcrdma_fixed_maxsz ; 
 unsigned int rpcrdma_segment_maxsz ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static unsigned int svc_rdma_reply_hdr_len(__be32 *rdma_resp)
{
	unsigned int nsegs;
	__be32 *p;

	p = rdma_resp;

	/* RPC-over-RDMA V1 replies never have a Read list. */
	p += rpcrdma_fixed_maxsz + 1;

	/* Skip Write list. */
	while (*p++ != xdr_zero) {
		nsegs = be32_to_cpup(p++);
		p += nsegs * rpcrdma_segment_maxsz;
	}

	/* Skip Reply chunk. */
	if (*p++ != xdr_zero) {
		nsegs = be32_to_cpup(p++);
		p += nsegs * rpcrdma_segment_maxsz;
	}

	return (unsigned long)p - (unsigned long)rdma_resp;
}