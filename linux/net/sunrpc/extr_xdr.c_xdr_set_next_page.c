#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {unsigned int page_ptr; int nwords; TYPE_1__* buf; } ;
struct TYPE_2__ {unsigned int pages; int /*<<< orphan*/  tail; scalar_t__ page_base; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  xdr_set_iov (struct xdr_stream*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xdr_set_page_base (struct xdr_stream*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdr_set_next_page(struct xdr_stream *xdr)
{
	unsigned int newbase;

	newbase = (1 + xdr->page_ptr - xdr->buf->pages) << PAGE_SHIFT;
	newbase -= xdr->buf->page_base;

	if (xdr_set_page_base(xdr, newbase, PAGE_SIZE) < 0)
		xdr_set_iov(xdr, xdr->buf->tail, xdr->nwords << 2);
}