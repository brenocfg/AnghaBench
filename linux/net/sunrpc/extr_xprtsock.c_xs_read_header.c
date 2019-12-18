#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_buf {TYPE_2__* head; } ;
struct TYPE_3__ {scalar_t__ copied; scalar_t__ offset; int /*<<< orphan*/  xid; } ;
struct sock_xprt {TYPE_1__ recv; } ;
struct TYPE_4__ {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
xs_read_header(struct sock_xprt *transport, struct xdr_buf *buf)
{
	if (!transport->recv.copied) {
		if (buf->head[0].iov_len >= transport->recv.offset)
			memcpy(buf->head[0].iov_base,
					&transport->recv.xid,
					transport->recv.offset);
		transport->recv.copied = transport->recv.offset;
	}
}