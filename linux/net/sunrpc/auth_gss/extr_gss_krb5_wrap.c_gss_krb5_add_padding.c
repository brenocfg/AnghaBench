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
struct xdr_buf {scalar_t__ len; struct kvec* head; struct kvec* tail; scalar_t__ page_len; } ;
struct kvec {int iov_len; char* iov_base; } ;

/* Variables and functions */
 int gss_krb5_padding (int,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static inline void
gss_krb5_add_padding(struct xdr_buf *buf, int offset, int blocksize)
{
	int padding = gss_krb5_padding(blocksize, buf->len - offset);
	char *p;
	struct kvec *iov;

	if (buf->page_len || buf->tail[0].iov_len)
		iov = &buf->tail[0];
	else
		iov = &buf->head[0];
	p = iov->iov_base + iov->iov_len;
	iov->iov_len += padding;
	buf->len += padding;
	memset(p, padding, padding);
}