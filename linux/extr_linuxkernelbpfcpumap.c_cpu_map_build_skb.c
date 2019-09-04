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
struct xdp_frame {int len; int headroom; int data; int /*<<< orphan*/  dev_rx; int /*<<< orphan*/  metasize; } ;
struct skb_shared_info {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct bpf_cpu_map_entry {int dummy; } ;

/* Variables and functions */
 int SKB_DATA_ALIGN (int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* build_skb (void*,unsigned int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_metadata_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *cpu_map_build_skb(struct bpf_cpu_map_entry *rcpu,
					 struct xdp_frame *xdpf)
{
	unsigned int frame_size;
	void *pkt_data_start;
	struct sk_buff *skb;

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
	frame_size = SKB_DATA_ALIGN(xdpf->len) + xdpf->headroom +
		SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

	pkt_data_start = xdpf->data - xdpf->headroom;
	skb = build_skb(pkt_data_start, frame_size);
	if (!skb)
		return NULL;

	skb_reserve(skb, xdpf->headroom);
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

	return skb;
}