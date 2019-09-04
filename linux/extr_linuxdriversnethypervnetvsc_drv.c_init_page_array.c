#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sk_buff {char* data; } ;
struct hv_page_buffer {int dummy; } ;
struct hv_netvsc_packet {size_t rmsg_size; size_t rmsg_pgcnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  page_offset; } ;
typedef  TYPE_1__ skb_frag_t ;
struct TYPE_6__ {int nr_frags; TYPE_1__* frags; } ;

/* Variables and functions */
 scalar_t__ fill_pg_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct hv_page_buffer*) ; 
 int /*<<< orphan*/  offset_in_page (char*) ; 
 int /*<<< orphan*/  skb_frag_page (TYPE_1__*) ; 
 size_t skb_frag_size (TYPE_1__*) ; 
 size_t skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  virt_to_page (char*) ; 

__attribute__((used)) static u32 init_page_array(void *hdr, u32 len, struct sk_buff *skb,
			   struct hv_netvsc_packet *packet,
			   struct hv_page_buffer *pb)
{
	u32 slots_used = 0;
	char *data = skb->data;
	int frags = skb_shinfo(skb)->nr_frags;
	int i;

	/* The packet is laid out thus:
	 * 1. hdr: RNDIS header and PPI
	 * 2. skb linear data
	 * 3. skb fragment data
	 */
	slots_used += fill_pg_buf(virt_to_page(hdr),
				  offset_in_page(hdr),
				  len, &pb[slots_used]);

	packet->rmsg_size = len;
	packet->rmsg_pgcnt = slots_used;

	slots_used += fill_pg_buf(virt_to_page(data),
				offset_in_page(data),
				skb_headlen(skb), &pb[slots_used]);

	for (i = 0; i < frags; i++) {
		skb_frag_t *frag = skb_shinfo(skb)->frags + i;

		slots_used += fill_pg_buf(skb_frag_page(frag),
					frag->page_offset,
					skb_frag_size(frag), &pb[slots_used]);
	}
	return slots_used;
}