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
struct xdr_stream {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xdr_stream_decode_opaque_fixed (struct xdr_stream*,void*,size_t) ; 

__attribute__((used)) static int decode_opaque_fixed(struct xdr_stream *xdr, void *buf, size_t len)
{
	ssize_t ret = xdr_stream_decode_opaque_fixed(xdr, buf, len);
	if (unlikely(ret < 0))
		return -EIO;
	return 0;
}