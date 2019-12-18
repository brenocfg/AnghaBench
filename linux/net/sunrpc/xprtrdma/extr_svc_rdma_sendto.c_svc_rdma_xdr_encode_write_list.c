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
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int rpcrdma_fixed_maxsz ; 
 unsigned int rpcrdma_segment_maxsz ; 
 unsigned int xdr_encode_write_chunk (scalar_t__*,scalar_t__*,unsigned int) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static void svc_rdma_xdr_encode_write_list(__be32 *rdma_resp, __be32 *wr_ch,
					   unsigned int consumed)
{
	unsigned int nsegs;
	__be32 *p, *q;

	/* RPC-over-RDMA V1 replies never have a Read list. */
	p = rdma_resp + rpcrdma_fixed_maxsz + 1;

	q = wr_ch;
	while (*q != xdr_zero) {
		nsegs = xdr_encode_write_chunk(p, q, consumed);
		q += 2 + nsegs * rpcrdma_segment_maxsz;
		p += 2 + nsegs * rpcrdma_segment_maxsz;
		consumed = 0;
	}

	/* Terminate Write list */
	*p++ = xdr_zero;

	/* Reply chunk discriminator; may be replaced later */
	*p = xdr_zero;
}