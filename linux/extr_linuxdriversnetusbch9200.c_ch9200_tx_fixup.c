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
struct usbnet {int maxpacket; } ;
struct sk_buff {int len; int* data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *ch9200_tx_fixup(struct usbnet *dev, struct sk_buff *skb,
				       gfp_t flags)
{
	int i = 0;
	int len = 0;
	int tx_overhead = 0;

	tx_overhead = 0x40;

	len = skb->len;
	if (skb_cow_head(skb, tx_overhead)) {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	__skb_push(skb, tx_overhead);
	/* usbnet adds padding if length is a multiple of packet size
	 * if so, adjust length value in header
	 */
	if ((skb->len % dev->maxpacket) == 0)
		len++;

	skb->data[0] = len;
	skb->data[1] = len >> 8;
	skb->data[2] = 0x00;
	skb->data[3] = 0x80;

	for (i = 4; i < 48; i++)
		skb->data[i] = 0x00;

	skb->data[48] = len;
	skb->data[49] = len >> 8;
	skb->data[50] = 0x00;
	skb->data[51] = 0x80;

	for (i = 52; i < 64; i++)
		skb->data[i] = 0x00;

	return skb;
}