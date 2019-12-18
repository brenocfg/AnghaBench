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
struct xdp_frame {int headroom; unsigned int len; int /*<<< orphan*/  dev_rx; scalar_t__ metasize; int /*<<< orphan*/  data; } ;
struct skb_shared_info {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct bpf_cpu_map_entry {int dummy; } ;

/* Variables and functions */
 unsigned int SKB_DATA_ALIGN (int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 struct sk_buff* build_skb_around (struct sk_buff*,void*,unsigned int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_metadata_set (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_release_frame (struct xdp_frame*) ; 
 int /*<<< orphan*/  xdp_scrub_frame (struct xdp_frame*) ; 

__attribute__((used)) static struct sk_buff *cpu_map_build_skb(struct bpf_cpu_map_entry *rcpu,
					 struct xdp_frame *xdpf,
					 struct sk_buff *skb)
{
	unsigned int hard_start_headroom;
	unsigned int frame_size;
	void *pkt_data_start;

	/* Part of headroom was reserved to xdpf */
	hard_start_headroom = sizeof(struct xdp_frame) +  xdpf->headroom;

	/* build_skb need to place skb_shared_info after SKB end, and
	 * also want to know the memory "truesize".  Thus, need to
	 * know the memory frame size backing xdp_buff.
	 *
	 * XDP was designed to have PAGE_SIZE frames, but this
	 * assumption is not longer true with ixgbe and i40e.  It
	 * would be preferred to set frame_size to 2048 or 4096
	 * depending on the driver.
	 *   frame_size = 2048;
	 *   frame_len  = frame_size - sizeof(*xdp_frame);
	 *
	 * Instead, with info avail, skb_shared_info in placed after
	 * packet len.  This, unfortunately fakes the truesize.
	 * Another disadvantage of this approach, the skb_shared_info
	 * is not at a fixed memory location, with mixed length
	 * packets, which is bad for cache-line hotness.
	 */
	frame_size = SKB_DATA_ALIGN(xdpf->len + hard_start_headroom) +
		SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

	pkt_data_start = xdpf->data - hard_start_headroom;
	skb = build_skb_around(skb, pkt_data_start, frame_size);
	if (unlikely(!skb))
		return NULL;

	skb_reserve(skb, hard_start_headroom);
	__skb_put(skb, xdpf->len);
	if (xdpf->metasize)
		skb_metadata_set(skb, xdpf->metasize);

	/* Essential SKB info: protocol and skb->dev */
	skb->protocol = eth_type_trans(skb, xdpf->dev_rx);

	/* Optional SKB info, currently missing:
	 * - HW checksum info		(skb->ip_summed)
	 * - HW RX hash			(skb_set_hash)
	 * - RX ring dev queue index	(skb_record_rx_queue)
	 */

	/* Until page_pool get SKB return path, release DMA here */
	xdp_release_frame(xdpf);

	/* Allow SKB to reuse area used by xdp_frame */
	xdp_scrub_frame(xdpf);

	return skb;
}