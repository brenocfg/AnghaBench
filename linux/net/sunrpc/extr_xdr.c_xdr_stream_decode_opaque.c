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
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 scalar_t__ xdr_stream_decode_opaque_inline (struct xdr_stream*,void**,size_t) ; 

ssize_t xdr_stream_decode_opaque(struct xdr_stream *xdr, void *ptr, size_t size)
{
	ssize_t ret;
	void *p;

	ret = xdr_stream_decode_opaque_inline(xdr, &p, size);
	if (ret <= 0)
		return ret;
	memcpy(ptr, p, ret);
	return ret;
}