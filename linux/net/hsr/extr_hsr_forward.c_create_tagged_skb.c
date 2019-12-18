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
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  csum_start; } ;
struct hsr_port {TYPE_1__* hsr; } ;
struct hsr_frame_info {scalar_t__ is_vlan; } ;
struct TYPE_2__ {int /*<<< orphan*/  prot_version; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HSR_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 struct sk_buff* __pskb_copy (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_fill_tag (struct sk_buff*,struct hsr_frame_info*,struct hsr_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 unsigned char* skb_mac_header (struct sk_buff*) ; 
 unsigned char* skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *create_tagged_skb(struct sk_buff *skb_o,
					 struct hsr_frame_info *frame,
					 struct hsr_port *port)
{
	int movelen;
	unsigned char *dst, *src;
	struct sk_buff *skb;

	/* Create the new skb with enough headroom to fit the HSR tag */
	skb = __pskb_copy(skb_o, skb_headroom(skb_o) + HSR_HLEN, GFP_ATOMIC);
	if (!skb)
		return NULL;
	skb_reset_mac_header(skb);

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start += HSR_HLEN;

	movelen = ETH_HLEN;
	if (frame->is_vlan)
		movelen += VLAN_HLEN;

	src = skb_mac_header(skb);
	dst = skb_push(skb, HSR_HLEN);
	memmove(dst, src, movelen);
	skb_reset_mac_header(skb);

	hsr_fill_tag(skb, frame, port, port->hsr->prot_version);

	return skb;
}