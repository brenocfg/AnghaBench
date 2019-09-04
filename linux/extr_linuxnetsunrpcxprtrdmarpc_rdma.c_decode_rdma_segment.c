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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xprtrdma_decode_seg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_rdma_segment(struct xdr_stream *xdr, u32 *length)
{
	u32 handle;
	u64 offset;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4 * sizeof(*p));
	if (unlikely(!p))
		return -EIO;

	handle = be32_to_cpup(p++);
	*length = be32_to_cpup(p++);
	xdr_decode_hyper(p, &offset);

	trace_xprtrdma_decode_seg(handle, *length, offset);
	return 0;
}