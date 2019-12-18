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
struct sk_buff {int dummy; } ;
struct nf_hook_state {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 unsigned int NF_VERDICT_FLAG_QUEUE_BYPASS ; 
 unsigned int NF_VERDICT_QBITS ; 
 int __nf_queue (struct sk_buff*,struct nf_hook_state*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

int nf_queue(struct sk_buff *skb, struct nf_hook_state *state,
	     unsigned int index, unsigned int verdict)
{
	int ret;

	ret = __nf_queue(skb, state, index, verdict >> NF_VERDICT_QBITS);
	if (ret < 0) {
		if (ret == -ESRCH &&
		    (verdict & NF_VERDICT_FLAG_QUEUE_BYPASS))
			return 1;
		kfree_skb(skb);
	}

	return 0;
}