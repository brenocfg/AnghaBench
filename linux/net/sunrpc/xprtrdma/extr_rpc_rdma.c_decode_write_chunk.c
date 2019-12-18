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
typedef  scalar_t__ u32 ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ decode_rdma_segment (struct xdr_stream*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_write_chunk(struct xdr_stream *xdr, u32 *length)
{
	u32 segcount, seglength;
	__be32 *p;

	p = xdr_inline_decode(xdr, sizeof(*p));
	if (unlikely(!p))
		return -EIO;

	*length = 0;
	segcount = be32_to_cpup(p);
	while (segcount--) {
		if (decode_rdma_segment(xdr, &seglength))
			return -EIO;
		*length += seglength;
	}

	return 0;
}