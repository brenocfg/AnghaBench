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
struct xdr_stream {scalar_t__ p; scalar_t__ end; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * __xdr_inline_decode (struct xdr_stream*,size_t) ; 
 int /*<<< orphan*/  trace_rpc_xdr_overflow (struct xdr_stream*,size_t) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_copy_to_scratch (struct xdr_stream*,size_t) ; 
 int /*<<< orphan*/  xdr_set_next_buffer (struct xdr_stream*) ; 

__be32 * xdr_inline_decode(struct xdr_stream *xdr, size_t nbytes)
{
	__be32 *p;

	if (unlikely(nbytes == 0))
		return xdr->p;
	if (xdr->p == xdr->end && !xdr_set_next_buffer(xdr))
		goto out_overflow;
	p = __xdr_inline_decode(xdr, nbytes);
	if (p != NULL)
		return p;
	return xdr_copy_to_scratch(xdr, nbytes);
out_overflow:
	trace_rpc_xdr_overflow(xdr, nbytes);
	return NULL;
}