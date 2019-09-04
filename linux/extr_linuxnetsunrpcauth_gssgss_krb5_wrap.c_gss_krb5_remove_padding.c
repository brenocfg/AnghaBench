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
typedef  int u8 ;
struct xdr_buf {size_t len; size_t page_len; size_t page_base; TYPE_2__* tail; int /*<<< orphan*/ * pages; TYPE_1__* head; } ;
struct TYPE_4__ {size_t iov_len; size_t iov_base; } ;
struct TYPE_3__ {size_t iov_len; size_t iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 size_t PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int*) ; 

__attribute__((used)) static inline int
gss_krb5_remove_padding(struct xdr_buf *buf, int blocksize)
{
	u8 *ptr;
	u8 pad;
	size_t len = buf->len;

	if (len <= buf->head[0].iov_len) {
		pad = *(u8 *)(buf->head[0].iov_base + len - 1);
		if (pad > buf->head[0].iov_len)
			return -EINVAL;
		buf->head[0].iov_len -= pad;
		goto out;
	} else
		len -= buf->head[0].iov_len;
	if (len <= buf->page_len) {
		unsigned int last = (buf->page_base + len - 1)
					>>PAGE_SHIFT;
		unsigned int offset = (buf->page_base + len - 1)
					& (PAGE_SIZE - 1);
		ptr = kmap_atomic(buf->pages[last]);
		pad = *(ptr + offset);
		kunmap_atomic(ptr);
		goto out;
	} else
		len -= buf->page_len;
	BUG_ON(len > buf->tail[0].iov_len);
	pad = *(u8 *)(buf->tail[0].iov_base + len - 1);
out:
	/* XXX: NOTE: we do not adjust the page lengths--they represent
	 * a range of data in the real filesystem page cache, and we need
	 * to know that range so the xdr code can properly place read data.
	 * However adjusting the head length, as we do above, is harmless.
	 * In the case of a request that fits into a single page, the server
	 * also uses length and head length together to determine the original
	 * start of the request to copy the request for deferal; so it's
	 * easier on the server if we adjust head and tail length in tandem.
	 * It's not really a problem that we don't fool with the page and
	 * tail lengths, though--at worst badly formed xdr might lead the
	 * server to attempt to parse the padding.
	 * XXX: Document all these weird requirements for gss mechanism
	 * wrap/unwrap functions. */
	if (pad > blocksize)
		return -EINVAL;
	if (buf->len > pad)
		buf->len -= pad;
	else
		return -EINVAL;
	return 0;
}