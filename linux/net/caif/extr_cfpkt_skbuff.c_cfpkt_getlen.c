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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 

inline u16 cfpkt_getlen(struct cfpkt *pkt)
{
	struct sk_buff *skb = pkt_to_skb(pkt);
	return skb->len;
}