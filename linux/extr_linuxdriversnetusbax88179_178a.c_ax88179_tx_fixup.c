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
typedef  int u32 ;
struct usbnet {int maxpacket; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int*,int) ; 
 scalar_t__ skb_header_cloned (struct sk_buff*) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
ax88179_tx_fixup(struct usbnet *dev, struct sk_buff *skb, gfp_t flags)
{
	u32 tx_hdr1, tx_hdr2;
	int frame_size = dev->maxpacket;
	int mss = skb_shinfo(skb)->gso_size;
	int headroom;

	tx_hdr1 = skb->len;
	tx_hdr2 = mss;
	if (((skb->len + 8) % frame_size) == 0)
		tx_hdr2 |= 0x80008000;	/* Enable padding */

	headroom = skb_headroom(skb) - 8;

	if ((skb_header_cloned(skb) || headroom < 0) &&
	    pskb_expand_head(skb, headroom < 0 ? 8 : 0, 0, GFP_ATOMIC)) {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	skb_push(skb, 4);
	cpu_to_le32s(&tx_hdr2);
	skb_copy_to_linear_data(skb, &tx_hdr2, 4);

	skb_push(skb, 4);
	cpu_to_le32s(&tx_hdr1);
	skb_copy_to_linear_data(skb, &tx_hdr1, 4);

	return skb;
}