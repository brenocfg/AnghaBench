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
struct xdr_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  buflen; scalar_t__ page_len; int /*<<< orphan*/ * tail; struct kvec* head; } ;
struct kvec {int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  empty_iov ; 

void
xdr_buf_from_iov(struct kvec *iov, struct xdr_buf *buf)
{
	buf->head[0] = *iov;
	buf->tail[0] = empty_iov;
	buf->page_len = 0;
	buf->buflen = buf->len = iov->iov_len;
}