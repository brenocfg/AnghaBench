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
struct xdr_stream {int /*<<< orphan*/ * iov; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; int /*<<< orphan*/ * page_ptr; TYPE_1__* buf; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {unsigned int page_len; int /*<<< orphan*/ * pages; scalar_t__ page_base; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 void* page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xdr_set_page_base(struct xdr_stream *xdr,
		unsigned int base, unsigned int len)
{
	unsigned int pgnr;
	unsigned int maxlen;
	unsigned int pgoff;
	unsigned int pgend;
	void *kaddr;

	maxlen = xdr->buf->page_len;
	if (base >= maxlen)
		return -EINVAL;
	maxlen -= base;
	if (len > maxlen)
		len = maxlen;

	base += xdr->buf->page_base;

	pgnr = base >> PAGE_SHIFT;
	xdr->page_ptr = &xdr->buf->pages[pgnr];
	kaddr = page_address(*xdr->page_ptr);

	pgoff = base & ~PAGE_MASK;
	xdr->p = (__be32*)(kaddr + pgoff);

	pgend = pgoff + len;
	if (pgend > PAGE_SIZE)
		pgend = PAGE_SIZE;
	xdr->end = (__be32*)(kaddr + pgend);
	xdr->iov = NULL;
	return 0;
}