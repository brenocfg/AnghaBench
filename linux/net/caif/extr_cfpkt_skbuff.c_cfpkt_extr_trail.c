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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int data; int len; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  PKT_ERROR (struct cfpkt*,char*) ; 
 int is_erronous (struct cfpkt*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int cfpkt_extr_trail(struct cfpkt *pkt, void *dta, u16 len)
{
	struct sk_buff *skb = pkt_to_skb(pkt);
	u8 *data = dta;
	u8 *from;
	if (unlikely(is_erronous(pkt)))
		return -EPROTO;

	if (unlikely(skb_linearize(skb) != 0)) {
		PKT_ERROR(pkt, "linearize failed\n");
		return -EPROTO;
	}
	if (unlikely(skb->data + len > skb_tail_pointer(skb))) {
		PKT_ERROR(pkt, "read beyond end of packet\n");
		return -EPROTO;
	}
	from = skb_tail_pointer(skb) - len;
	skb_trim(skb, skb->len - len);
	memcpy(data, from, len);
	return 0;
}