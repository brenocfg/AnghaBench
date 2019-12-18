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
typedef  size_t (* xdr_skb_read_actor ) (struct xdr_skb_reader*,char*,unsigned int) ;
struct xdr_skb_reader {int /*<<< orphan*/  count; } ;
struct xdr_buf {unsigned int page_len; int flags; TYPE_2__* tail; scalar_t__ page_base; TYPE_1__* head; struct page** pages; } ;
struct page {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {unsigned int iov_len; scalar_t__ iov_base; } ;
struct TYPE_3__ {unsigned int iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 size_t ENOMEM ; 
 int GFP_NOWAIT ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int XDRBUF_SPARSE_PAGES ; 
 int __GFP_NOWARN ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t
xdr_partial_copy_from_skb(struct xdr_buf *xdr, unsigned int base, struct xdr_skb_reader *desc, xdr_skb_read_actor copy_actor)
{
	struct page	**ppage = xdr->pages;
	unsigned int	len, pglen = xdr->page_len;
	ssize_t		copied = 0;
	size_t		ret;

	len = xdr->head[0].iov_len;
	if (base < len) {
		len -= base;
		ret = copy_actor(desc, (char *)xdr->head[0].iov_base + base, len);
		copied += ret;
		if (ret != len || !desc->count)
			goto out;
		base = 0;
	} else
		base -= len;

	if (unlikely(pglen == 0))
		goto copy_tail;
	if (unlikely(base >= pglen)) {
		base -= pglen;
		goto copy_tail;
	}
	if (base || xdr->page_base) {
		pglen -= base;
		base += xdr->page_base;
		ppage += base >> PAGE_SHIFT;
		base &= ~PAGE_MASK;
	}
	do {
		char *kaddr;

		/* ACL likes to be lazy in allocating pages - ACLs
		 * are small by default but can get huge. */
		if ((xdr->flags & XDRBUF_SPARSE_PAGES) && *ppage == NULL) {
			*ppage = alloc_page(GFP_NOWAIT | __GFP_NOWARN);
			if (unlikely(*ppage == NULL)) {
				if (copied == 0)
					copied = -ENOMEM;
				goto out;
			}
		}

		len = PAGE_SIZE;
		kaddr = kmap_atomic(*ppage);
		if (base) {
			len -= base;
			if (pglen < len)
				len = pglen;
			ret = copy_actor(desc, kaddr + base, len);
			base = 0;
		} else {
			if (pglen < len)
				len = pglen;
			ret = copy_actor(desc, kaddr, len);
		}
		flush_dcache_page(*ppage);
		kunmap_atomic(kaddr);
		copied += ret;
		if (ret != len || !desc->count)
			goto out;
		ppage++;
	} while ((pglen -= len) != 0);
copy_tail:
	len = xdr->tail[0].iov_len;
	if (base < len)
		copied += copy_actor(desc, (char *)xdr->tail[0].iov_base + base, len - base);
out:
	return copied;
}