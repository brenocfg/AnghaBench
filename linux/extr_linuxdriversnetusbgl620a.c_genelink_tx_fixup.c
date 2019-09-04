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
struct sk_buff {int len; int /*<<< orphan*/  data; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
genelink_tx_fixup(struct usbnet *dev, struct sk_buff *skb, gfp_t flags)
{
	int 	padlen;
	int	length = skb->len;
	int	headroom = skb_headroom(skb);
	int	tailroom = skb_tailroom(skb);
	__le32	*packet_count;
	__le32	*packet_len;

	// FIXME:  magic numbers, bleech
	padlen = ((skb->len + (4 + 4*1)) % 64) ? 0 : 1;

	if ((!skb_cloned(skb))
			&& ((headroom + tailroom) >= (padlen + (4 + 4*1)))) {
		if ((headroom < (4 + 4*1)) || (tailroom < padlen)) {
			skb->data = memmove(skb->head + (4 + 4*1),
					     skb->data, skb->len);
			skb_set_tail_pointer(skb, skb->len);
		}
	} else {
		struct sk_buff	*skb2;
		skb2 = skb_copy_expand(skb, (4 + 4*1) , padlen, flags);
		dev_kfree_skb_any(skb);
		skb = skb2;
		if (!skb)
			return NULL;
	}

	// attach the packet count to the header
	packet_count = skb_push(skb, (4 + 4 * 1));
	packet_len = packet_count + 1;

	*packet_count = cpu_to_le32(1);
	*packet_len = cpu_to_le32(length);

	// add padding byte
	if ((skb->len % dev->maxpacket) == 0)
		skb_put(skb, 1);

	return skb;
}