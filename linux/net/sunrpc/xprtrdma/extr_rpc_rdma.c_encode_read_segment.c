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
struct xdr_stream {int dummy; } ;
struct rpcrdma_mr {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdr_encode_rdma_segment (int /*<<< orphan*/ *,struct rpcrdma_mr*) ; 
 int /*<<< orphan*/  xdr_one ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static int
encode_read_segment(struct xdr_stream *xdr, struct rpcrdma_mr *mr,
		    u32 position)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 6 * sizeof(*p));
	if (unlikely(!p))
		return -EMSGSIZE;

	*p++ = xdr_one;			/* Item present */
	*p++ = cpu_to_be32(position);
	xdr_encode_rdma_segment(p, mr);
	return 0;
}