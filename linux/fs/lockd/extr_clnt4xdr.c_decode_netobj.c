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
struct xdr_netobj {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  XDR_MAX_NETOBJ ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xdr_stream_decode_opaque_inline (struct xdr_stream*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_netobj(struct xdr_stream *xdr,
			 struct xdr_netobj *obj)
{
	ssize_t ret;

	ret = xdr_stream_decode_opaque_inline(xdr, (void *)&obj->data,
						XDR_MAX_NETOBJ);
	if (unlikely(ret < 0))
		return -EIO;
	obj->len = ret;
	return 0;
}