#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {struct sk_buff* next; scalar_t__ sk; } ;
struct TYPE_2__ {scalar_t__ nr_frags; struct sk_buff* frag_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * __pskb_pull_tail (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_has_frag_list (struct sk_buff*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_pagelen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int skb_cow_data(struct sk_buff *skb, int tailbits, struct sk_buff **trailer)
{
	int copyflag;
	int elt;
	struct sk_buff *skb1, **skb_p;

	/* If skb is cloned or its head is paged, reallocate
	 * head pulling out all the pages (pages are considered not writable
	 * at the moment even if they are anonymous).
	 */
	if ((skb_cloned(skb) || skb_shinfo(skb)->nr_frags) &&
	    __pskb_pull_tail(skb, skb_pagelen(skb)-skb_headlen(skb)) == NULL)
		return -ENOMEM;

	/* Easy case. Most of packets will go this way. */
	if (!skb_has_frag_list(skb)) {
		/* A little of trouble, not enough of space for trailer.
		 * This should not happen, when stack is tuned to generate
		 * good frames. OK, on miss we reallocate and reserve even more
		 * space, 128 bytes is fair. */

		if (skb_tailroom(skb) < tailbits &&
		    pskb_expand_head(skb, 0, tailbits-skb_tailroom(skb)+128, GFP_ATOMIC))
			return -ENOMEM;

		/* Voila! */
		*trailer = skb;
		return 1;
	}

	/* Misery. We are in troubles, going to mincer fragments... */

	elt = 1;
	skb_p = &skb_shinfo(skb)->frag_list;
	copyflag = 0;

	while ((skb1 = *skb_p) != NULL) {
		int ntail = 0;

		/* The fragment is partially pulled by someone,
		 * this can happen on input. Copy it and everything
		 * after it. */

		if (skb_shared(skb1))
			copyflag = 1;

		/* If the skb is the last, worry about trailer. */

		if (skb1->next == NULL && tailbits) {
			if (skb_shinfo(skb1)->nr_frags ||
			    skb_has_frag_list(skb1) ||
			    skb_tailroom(skb1) < tailbits)
				ntail = tailbits + 128;
		}

		if (copyflag ||
		    skb_cloned(skb1) ||
		    ntail ||
		    skb_shinfo(skb1)->nr_frags ||
		    skb_has_frag_list(skb1)) {
			struct sk_buff *skb2;

			/* Fuck, we are miserable poor guys... */
			if (ntail == 0)
				skb2 = skb_copy(skb1, GFP_ATOMIC);
			else
				skb2 = skb_copy_expand(skb1,
						       skb_headroom(skb1),
						       ntail,
						       GFP_ATOMIC);
			if (unlikely(skb2 == NULL))
				return -ENOMEM;

			if (skb1->sk)
				skb_set_owner_w(skb2, skb1->sk);

			/* Looking around. Are we still alive?
			 * OK, link new skb, drop old one */

			skb2->next = skb1->next;
			*skb_p = skb2;
			kfree_skb(skb1);
			skb1 = skb2;
		}
		elt++;
		*trailer = skb1;
		skb_p = &skb1->next;
	}

	return elt;
}