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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfpkt_add_head (struct cfpkt*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_extr_head (struct cfpkt*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 

int cfpkt_peek_head(struct cfpkt *pkt, void *data, u16 len)
{
	struct sk_buff *skb = pkt_to_skb(pkt);
	if (skb_headlen(skb) >= len) {
		memcpy(data, skb->data, len);
		return 0;
	}
	return !cfpkt_extr_head(pkt, data, len) &&
	    !cfpkt_add_head(pkt, data, len);
}