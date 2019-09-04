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
struct virtnet_info {unsigned int hdr_len; scalar_t__ mergeable_rx_bufs; } ;
struct virtio_net_hdr_mrg_rxbuf {int dummy; } ;
struct sk_buff {TYPE_1__* dev; } ;
struct receive_queue {int /*<<< orphan*/  napi; } ;
struct page {scalar_t__ private; } ;
struct padded_vnet_hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GOOD_COPY_LEN ; 
 unsigned int MAX_SKB_FRAGS ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  give_pages (struct receive_queue*,struct page*) ; 
 int /*<<< orphan*/  memcpy (struct virtio_net_hdr_mrg_rxbuf*,char*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int /*<<< orphan*/ ) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,char*,unsigned int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_tailroom (struct sk_buff*) ; 
 struct virtio_net_hdr_mrg_rxbuf* skb_vnet_hdr (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *page_to_skb(struct virtnet_info *vi,
				   struct receive_queue *rq,
				   struct page *page, unsigned int offset,
				   unsigned int len, unsigned int truesize,
				   bool hdr_valid)
{
	struct sk_buff *skb;
	struct virtio_net_hdr_mrg_rxbuf *hdr;
	unsigned int copy, hdr_len, hdr_padded_len;
	char *p;

	p = page_address(page) + offset;

	/* copy small packet so we can reuse these pages for small data */
	skb = napi_alloc_skb(&rq->napi, GOOD_COPY_LEN);
	if (unlikely(!skb))
		return NULL;

	hdr = skb_vnet_hdr(skb);

	hdr_len = vi->hdr_len;
	if (vi->mergeable_rx_bufs)
		hdr_padded_len = sizeof(*hdr);
	else
		hdr_padded_len = sizeof(struct padded_vnet_hdr);

	if (hdr_valid)
		memcpy(hdr, p, hdr_len);

	len -= hdr_len;
	offset += hdr_padded_len;
	p += hdr_padded_len;

	copy = len;
	if (copy > skb_tailroom(skb))
		copy = skb_tailroom(skb);
	skb_put_data(skb, p, copy);

	len -= copy;
	offset += copy;

	if (vi->mergeable_rx_bufs) {
		if (len)
			skb_add_rx_frag(skb, 0, page, offset, len, truesize);
		else
			put_page(page);
		return skb;
	}

	/*
	 * Verify that we can indeed put this data into a skb.
	 * This is here to handle cases when the device erroneously
	 * tries to receive more than is possible. This is usually
	 * the case of a broken device.
	 */
	if (unlikely(len > MAX_SKB_FRAGS * PAGE_SIZE)) {
		net_dbg_ratelimited("%s: too much data\n", skb->dev->name);
		dev_kfree_skb(skb);
		return NULL;
	}
	BUG_ON(offset >= PAGE_SIZE);
	while (len) {
		unsigned int frag_size = min((unsigned)PAGE_SIZE - offset, len);
		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page, offset,
				frag_size, truesize);
		len -= frag_size;
		page = (struct page *)page->private;
		offset = 0;
	}

	if (page)
		give_pages(rq, page);

	return skb;
}