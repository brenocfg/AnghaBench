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
typedef  int u32 ;
struct usbnet {int maxpacket; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  padbytes ;
typedef  int /*<<< orphan*/  packet_len ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int*,int) ; 
 int /*<<< orphan*/  skb_header_cloned (struct sk_buff*) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  usbnet_set_skb_tx_stats (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

struct sk_buff *asix_tx_fixup(struct usbnet *dev, struct sk_buff *skb,
			      gfp_t flags)
{
	int padlen;
	int headroom = skb_headroom(skb);
	int tailroom = skb_tailroom(skb);
	u32 packet_len;
	u32 padbytes = 0xffff0000;

	padlen = ((skb->len + 4) & (dev->maxpacket - 1)) ? 0 : 4;

	/* We need to push 4 bytes in front of frame (packet_len)
	 * and maybe add 4 bytes after the end (if padlen is 4)
	 *
	 * Avoid skb_copy_expand() expensive call, using following rules :
	 * - We are allowed to push 4 bytes in headroom if skb_header_cloned()
	 *   is false (and if we have 4 bytes of headroom)
	 * - We are allowed to put 4 bytes at tail if skb_cloned()
	 *   is false (and if we have 4 bytes of tailroom)
	 *
	 * TCP packets for example are cloned, but __skb_header_release()
	 * was called in tcp stack, allowing us to use headroom for our needs.
	 */
	if (!skb_header_cloned(skb) &&
	    !(padlen && skb_cloned(skb)) &&
	    headroom + tailroom >= 4 + padlen) {
		/* following should not happen, but better be safe */
		if (headroom < 4 ||
		    tailroom < padlen) {
			skb->data = memmove(skb->head + 4, skb->data, skb->len);
			skb_set_tail_pointer(skb, skb->len);
		}
	} else {
		struct sk_buff *skb2;

		skb2 = skb_copy_expand(skb, 4, padlen, flags);
		dev_kfree_skb_any(skb);
		skb = skb2;
		if (!skb)
			return NULL;
	}

	packet_len = ((skb->len ^ 0x0000ffff) << 16) + skb->len;
	skb_push(skb, 4);
	cpu_to_le32s(&packet_len);
	skb_copy_to_linear_data(skb, &packet_len, sizeof(packet_len));

	if (padlen) {
		cpu_to_le32s(&padbytes);
		memcpy(skb_tail_pointer(skb), &padbytes, sizeof(padbytes));
		skb_put(skb, sizeof(padbytes));
	}

	usbnet_set_skb_tx_stats(skb, 1, 0);
	return skb;
}