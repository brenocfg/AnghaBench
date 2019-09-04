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
typedef  scalar_t__ u16 ;
struct skb_shared_info {int dummy; } ;
struct receive_queue {int /*<<< orphan*/  vq; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PAGE_SIZE ; 
 int SKB_DATA_ALIGN (int) ; 
 int VIRTIO_XDP_HEADROOM ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void*) ; 
 void* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static struct page *xdp_linearize_page(struct receive_queue *rq,
				       u16 *num_buf,
				       struct page *p,
				       int offset,
				       int page_off,
				       unsigned int *len)
{
	struct page *page = alloc_page(GFP_ATOMIC);

	if (!page)
		return NULL;

	memcpy(page_address(page) + page_off, page_address(p) + offset, *len);
	page_off += *len;

	while (--*num_buf) {
		int tailroom = SKB_DATA_ALIGN(sizeof(struct skb_shared_info));
		unsigned int buflen;
		void *buf;
		int off;

		buf = virtqueue_get_buf(rq->vq, &buflen);
		if (unlikely(!buf))
			goto err_buf;

		p = virt_to_head_page(buf);
		off = buf - page_address(p);

		/* guard against a misconfigured or uncooperative backend that
		 * is sending packet larger than the MTU.
		 */
		if ((page_off + buflen + tailroom) > PAGE_SIZE) {
			put_page(p);
			goto err_buf;
		}

		memcpy(page_address(page) + page_off,
		       page_address(p) + off, buflen);
		page_off += buflen;
		put_page(p);
	}

	/* Headroom does not contribute to packet length */
	*len = page_off - VIRTIO_XDP_HEADROOM;
	return page;
err_buf:
	__free_pages(page, 0);
	return NULL;
}