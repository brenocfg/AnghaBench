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
struct sk_buff {unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int pskb_trim_rcsum (struct sk_buff*,unsigned int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *skb_checksum_maybe_trim(struct sk_buff *skb,
					       unsigned int transport_len)
{
	struct sk_buff *skb_chk;
	unsigned int len = skb_transport_offset(skb) + transport_len;
	int ret;

	if (skb->len < len)
		return NULL;
	else if (skb->len == len)
		return skb;

	skb_chk = skb_clone(skb, GFP_ATOMIC);
	if (!skb_chk)
		return NULL;

	ret = pskb_trim_rcsum(skb_chk, len);
	if (ret) {
		kfree_skb(skb_chk);
		return NULL;
	}

	return skb_chk;
}