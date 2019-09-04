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
struct skb_shared_info {struct sk_buff* frag_list; } ;
struct sk_buff {int len; struct sk_buff* next; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ pskb_carve (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 

__attribute__((used)) static int pskb_carve_frag_list(struct sk_buff *skb,
				struct skb_shared_info *shinfo, int eat,
				gfp_t gfp_mask)
{
	struct sk_buff *list = shinfo->frag_list;
	struct sk_buff *clone = NULL;
	struct sk_buff *insp = NULL;

	do {
		if (!list) {
			pr_err("Not enough bytes to eat. Want %d\n", eat);
			return -EFAULT;
		}
		if (list->len <= eat) {
			/* Eaten as whole. */
			eat -= list->len;
			list = list->next;
			insp = list;
		} else {
			/* Eaten partially. */
			if (skb_shared(list)) {
				clone = skb_clone(list, gfp_mask);
				if (!clone)
					return -ENOMEM;
				insp = list->next;
				list = clone;
			} else {
				/* This may be pulled without problems. */
				insp = list;
			}
			if (pskb_carve(list, eat, gfp_mask) < 0) {
				kfree_skb(clone);
				return -ENOMEM;
			}
			break;
		}
	} while (eat);

	/* Free pulled out fragments. */
	while ((list = shinfo->frag_list) != insp) {
		shinfo->frag_list = list->next;
		kfree_skb(list);
	}
	/* And insert new clone at head. */
	if (clone) {
		clone->next = list;
		shinfo->frag_list = clone;
	}
	return 0;
}