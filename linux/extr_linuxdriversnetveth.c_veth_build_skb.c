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
struct skb_shared_info {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int SKB_DATA_ALIGN (int) ; 
 struct sk_buff* build_skb (void*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *veth_build_skb(void *head, int headroom, int len,
				      int buflen)
{
	struct sk_buff *skb;

	if (!buflen) {
		buflen = SKB_DATA_ALIGN(headroom + len) +
			 SKB_DATA_ALIGN(sizeof(struct skb_shared_info));
	}
	skb = build_skb(head, buflen);
	if (!skb)
		return NULL;

	skb_reserve(skb, headroom);
	skb_put(skb, len);

	return skb;
}