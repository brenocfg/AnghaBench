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
struct usbnet {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
zaurus_tx_fixup(struct usbnet *dev, struct sk_buff *skb, gfp_t flags)
{
	int			padlen;
	struct sk_buff		*skb2;

	padlen = 2;
	if (!skb_cloned(skb)) {
		int	tailroom = skb_tailroom(skb);
		if ((padlen + 4) <= tailroom)
			goto done;
	}
	skb2 = skb_copy_expand(skb, 0, 4 + padlen, flags);
	dev_kfree_skb_any(skb);
	skb = skb2;
	if (skb) {
		u32		fcs;
done:
		fcs = crc32_le(~0, skb->data, skb->len);
		fcs = ~fcs;

		skb_put_u8(skb, fcs & 0xff);
		skb_put_u8(skb, (fcs >> 8) & 0xff);
		skb_put_u8(skb, (fcs >> 16) & 0xff);
		skb_put_u8(skb, (fcs >> 24) & 0xff);
	}
	return skb;
}