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
struct xdr_buf {unsigned int page_len; long page_base; int flags; TYPE_2__* tail; struct page** pages; TYPE_2__* head; } ;
struct TYPE_3__ {scalar_t__ ri_implicit_roundup; } ;
struct rpcrdma_xprt {TYPE_1__ rx_ia; } ;
struct rpcrdma_mr_seg {char* mr_offset; unsigned int mr_len; struct page* mr_page; } ;
struct page {int dummy; } ;
typedef  enum rpcrdma_chunktype { ____Placeholder_rpcrdma_chunktype } rpcrdma_chunktype ;
struct TYPE_4__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 int EIO ; 
 int ENOBUFS ; 
 int GFP_NOWAIT ; 
 long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int RPCRDMA_MAX_SEGS ; 
 int XDRBUF_SPARSE_PAGES ; 
 int __GFP_NOWARN ; 
 struct page* alloc_page (int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 unsigned long offset_in_page (long) ; 
 struct rpcrdma_mr_seg* rpcrdma_convert_kvec (TYPE_2__*,struct rpcrdma_mr_seg*,unsigned int*) ; 
 int rpcrdma_readch ; 
 int rpcrdma_writech ; 
 int /*<<< orphan*/  u32 ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
rpcrdma_convert_iovs(struct rpcrdma_xprt *r_xprt, struct xdr_buf *xdrbuf,
		     unsigned int pos, enum rpcrdma_chunktype type,
		     struct rpcrdma_mr_seg *seg)
{
	unsigned long page_base;
	unsigned int len, n;
	struct page **ppages;

	n = 0;
	if (pos == 0)
		seg = rpcrdma_convert_kvec(&xdrbuf->head[0], seg, &n);

	len = xdrbuf->page_len;
	ppages = xdrbuf->pages + (xdrbuf->page_base >> PAGE_SHIFT);
	page_base = offset_in_page(xdrbuf->page_base);
	while (len) {
		/* ACL likes to be lazy in allocating pages - ACLs
		 * are small by default but can get huge.
		 */
		if (unlikely(xdrbuf->flags & XDRBUF_SPARSE_PAGES)) {
			if (!*ppages)
				*ppages = alloc_page(GFP_NOWAIT | __GFP_NOWARN);
			if (!*ppages)
				return -ENOBUFS;
		}
		seg->mr_page = *ppages;
		seg->mr_offset = (char *)page_base;
		seg->mr_len = min_t(u32, PAGE_SIZE - page_base, len);
		len -= seg->mr_len;
		++ppages;
		++seg;
		++n;
		page_base = 0;
	}

	/* When encoding a Read chunk, the tail iovec contains an
	 * XDR pad and may be omitted.
	 */
	if (type == rpcrdma_readch && r_xprt->rx_ia.ri_implicit_roundup)
		goto out;

	/* When encoding a Write chunk, some servers need to see an
	 * extra segment for non-XDR-aligned Write chunks. The upper
	 * layer provides space in the tail iovec that may be used
	 * for this purpose.
	 */
	if (type == rpcrdma_writech && r_xprt->rx_ia.ri_implicit_roundup)
		goto out;

	if (xdrbuf->tail[0].iov_len)
		seg = rpcrdma_convert_kvec(&xdrbuf->tail[0], seg, &n);

out:
	if (unlikely(n > RPCRDMA_MAX_SEGS))
		return -EIO;
	return n;
}