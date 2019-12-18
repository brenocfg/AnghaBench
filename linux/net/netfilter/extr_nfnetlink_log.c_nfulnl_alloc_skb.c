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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int __GFP_NOWARN ; 
 struct sk_buff* alloc_skb (unsigned int,int) ; 
 unsigned int max (unsigned int,unsigned int) ; 

__attribute__((used)) static struct sk_buff *
nfulnl_alloc_skb(struct net *net, u32 peer_portid, unsigned int inst_size,
		 unsigned int pkt_size)
{
	struct sk_buff *skb;
	unsigned int n;

	/* alloc skb which should be big enough for a whole multipart
	 * message.  WARNING: has to be <= 128k due to slab restrictions */

	n = max(inst_size, pkt_size);
	skb = alloc_skb(n, GFP_ATOMIC | __GFP_NOWARN);
	if (!skb) {
		if (n > pkt_size) {
			/* try to allocate only as much as we need for current
			 * packet */

			skb = alloc_skb(pkt_size, GFP_ATOMIC);
		}
	}

	return skb;
}