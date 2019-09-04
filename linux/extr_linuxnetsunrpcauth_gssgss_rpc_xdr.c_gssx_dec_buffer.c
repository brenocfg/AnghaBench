#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xdr_stream {int dummy; } ;
struct TYPE_3__ {int len; scalar_t__ data; } ;
typedef  TYPE_1__ gssx_buffer ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int gssx_dec_buffer(struct xdr_stream *xdr,
			   gssx_buffer *buf)
{
	u32 length;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(p == NULL))
		return -ENOSPC;

	length = be32_to_cpup(p);
	p = xdr_inline_decode(xdr, length);
	if (unlikely(p == NULL))
		return -ENOSPC;

	if (buf->len == 0) {
		/* we intentionally are not interested in this buffer */
		return 0;
	}
	if (length > buf->len)
		return -ENOSPC;

	if (!buf->data) {
		buf->data = kmemdup(p, length, GFP_KERNEL);
		if (!buf->data)
			return -ENOMEM;
	} else {
		memcpy(buf->data, p, length);
	}
	buf->len = length;
	return 0;
}