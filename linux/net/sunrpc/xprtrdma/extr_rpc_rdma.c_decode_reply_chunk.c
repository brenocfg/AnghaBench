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
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ decode_write_chunk (struct xdr_stream*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__* xdr_inline_decode (struct xdr_stream*,int) ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static int decode_reply_chunk(struct xdr_stream *xdr, u32 *length)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, sizeof(*p));
	if (unlikely(!p))
		return -EIO;

	*length = 0;
	if (*p != xdr_zero)
		if (decode_write_chunk(xdr, length))
			return -EIO;
	return 0;
}