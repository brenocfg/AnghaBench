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
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct nf_queue_entry {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ pskb_trim (struct sk_buff*,int) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void*,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int
nfqnl_mangle(void *data, int data_len, struct nf_queue_entry *e, int diff)
{
	struct sk_buff *nskb;

	if (diff < 0) {
		if (pskb_trim(e->skb, data_len))
			return -ENOMEM;
	} else if (diff > 0) {
		if (data_len > 0xFFFF)
			return -EINVAL;
		if (diff > skb_tailroom(e->skb)) {
			nskb = skb_copy_expand(e->skb, skb_headroom(e->skb),
					       diff, GFP_ATOMIC);
			if (!nskb)
				return -ENOMEM;
			kfree_skb(e->skb);
			e->skb = nskb;
		}
		skb_put(e->skb, diff);
	}
	if (skb_ensure_writable(e->skb, data_len))
		return -ENOMEM;
	skb_copy_to_linear_data(e->skb, data, data_len);
	e->skb->ip_summed = CHECKSUM_NONE;
	return 0;
}