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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int data; int len; int data_len; unsigned int truesize; int /*<<< orphan*/  protocol; } ;
struct efx_rx_buffer {int len; int page_offset; int /*<<< orphan*/ * page; } ;
struct efx_nic {int rx_ip_align; int rx_prefix_size; unsigned int rx_buffer_truesize; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  rx_buffer_order; int /*<<< orphan*/  n_rx_noskb_drops; } ;
struct efx_channel {int /*<<< orphan*/  napi_str; int /*<<< orphan*/  rx_queue; struct efx_nic* efx; } ;
struct TYPE_2__ {unsigned int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct efx_rx_buffer* efx_rx_buf_next (int /*<<< orphan*/ *,struct efx_rx_buffer*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  skb_mark_napi_id (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *efx_rx_mk_skb(struct efx_channel *channel,
				     struct efx_rx_buffer *rx_buf,
				     unsigned int n_frags,
				     u8 *eh, int hdr_len)
{
	struct efx_nic *efx = channel->efx;
	struct sk_buff *skb;

	/* Allocate an SKB to store the headers */
	skb = netdev_alloc_skb(efx->net_dev,
			       efx->rx_ip_align + efx->rx_prefix_size +
			       hdr_len);
	if (unlikely(skb == NULL)) {
		atomic_inc(&efx->n_rx_noskb_drops);
		return NULL;
	}

	EFX_WARN_ON_ONCE_PARANOID(rx_buf->len < hdr_len);

	memcpy(skb->data + efx->rx_ip_align, eh - efx->rx_prefix_size,
	       efx->rx_prefix_size + hdr_len);
	skb_reserve(skb, efx->rx_ip_align + efx->rx_prefix_size);
	__skb_put(skb, hdr_len);

	/* Append the remaining page(s) onto the frag list */
	if (rx_buf->len > hdr_len) {
		rx_buf->page_offset += hdr_len;
		rx_buf->len -= hdr_len;

		for (;;) {
			skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
					   rx_buf->page, rx_buf->page_offset,
					   rx_buf->len);
			rx_buf->page = NULL;
			skb->len += rx_buf->len;
			skb->data_len += rx_buf->len;
			if (skb_shinfo(skb)->nr_frags == n_frags)
				break;

			rx_buf = efx_rx_buf_next(&channel->rx_queue, rx_buf);
		}
	} else {
		__free_pages(rx_buf->page, efx->rx_buffer_order);
		rx_buf->page = NULL;
		n_frags = 0;
	}

	skb->truesize += n_frags * efx->rx_buffer_truesize;

	/* Move past the ethernet header */
	skb->protocol = eth_type_trans(skb, efx->net_dev);

	skb_mark_napi_id(skb, &channel->napi_str);

	return skb;
}