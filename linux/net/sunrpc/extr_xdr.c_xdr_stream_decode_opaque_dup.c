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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 void* kmemdup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_stream_decode_opaque_inline (struct xdr_stream*,void**,size_t) ; 

ssize_t xdr_stream_decode_opaque_dup(struct xdr_stream *xdr, void **ptr,
		size_t maxlen, gfp_t gfp_flags)
{
	ssize_t ret;
	void *p;

	ret = xdr_stream_decode_opaque_inline(xdr, &p, maxlen);
	if (ret > 0) {
		*ptr = kmemdup(p, ret, gfp_flags);
		if (*ptr != NULL)
			return ret;
		ret = -ENOMEM;
	}
	*ptr = NULL;
	return ret;
}