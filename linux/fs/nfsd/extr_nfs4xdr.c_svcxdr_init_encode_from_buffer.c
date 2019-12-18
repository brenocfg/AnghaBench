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
struct TYPE_3__ {scalar_t__ iov_len; } ;
struct xdr_stream {void* end; int /*<<< orphan*/ * p; TYPE_2__* iov; struct xdr_buf* buf; TYPE_1__ scratch; } ;
struct xdr_buf {int buflen; TYPE_2__* head; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct xdr_buf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void svcxdr_init_encode_from_buffer(struct xdr_stream *xdr,
				struct xdr_buf *buf, __be32 *p, int bytes)
{
	xdr->scratch.iov_len = 0;
	memset(buf, 0, sizeof(struct xdr_buf));
	buf->head[0].iov_base = p;
	buf->head[0].iov_len = 0;
	buf->len = 0;
	xdr->buf = buf;
	xdr->iov = buf->head;
	xdr->p = p;
	xdr->end = (void *)p + bytes;
	buf->buflen = bytes;
}