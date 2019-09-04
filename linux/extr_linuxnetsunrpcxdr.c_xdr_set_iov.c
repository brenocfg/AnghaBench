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
struct xdr_stream {int /*<<< orphan*/ * page_ptr; struct kvec* iov; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; } ;
struct kvec {unsigned int iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */

__attribute__((used)) static void xdr_set_iov(struct xdr_stream *xdr, struct kvec *iov,
		unsigned int len)
{
	if (len > iov->iov_len)
		len = iov->iov_len;
	xdr->p = (__be32*)iov->iov_base;
	xdr->end = (__be32*)(iov->iov_base + len);
	xdr->iov = iov;
	xdr->page_ptr = NULL;
}