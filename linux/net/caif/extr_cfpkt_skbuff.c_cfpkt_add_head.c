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
struct sk_buff {int dummy; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  PKT_ERROR (struct cfpkt*,char*) ; 
 int is_erronous (struct cfpkt*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int cfpkt_add_head(struct cfpkt *pkt, const void *data2, u16 len)
{
	struct sk_buff *skb = pkt_to_skb(pkt);
	struct sk_buff *lastskb;
	u8 *to;
	const u8 *data = data2;
	int ret;
	if (unlikely(is_erronous(pkt)))
		return -EPROTO;
	if (unlikely(skb_headroom(skb) < len)) {
		PKT_ERROR(pkt, "no headroom\n");
		return -EPROTO;
	}

	/* Make sure data is writable */
	ret = skb_cow_data(skb, 0, &lastskb);
	if (unlikely(ret < 0)) {
		PKT_ERROR(pkt, "cow failed\n");
		return ret;
	}

	to = skb_push(skb, len);
	memcpy(to, data, len);
	return 0;
}