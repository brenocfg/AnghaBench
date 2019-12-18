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
struct sk_buff {int tail; int end; int len; scalar_t__ data_len; struct sk_buff* next; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; struct sk_buff* frag_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  skb_frag_off_add (int /*<<< orphan*/ *,int) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_unref (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_has_frag_list (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 void* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_zcopy_clear (struct sk_buff*,int) ; 

void *__pskb_pull_tail(struct sk_buff *skb, int delta)
{
	/* If skb has not enough free space at tail, get new one
	 * plus 128 bytes for future expansions. If we have enough
	 * room at tail, reallocate without expansion only if skb is cloned.
	 */
	int i, k, eat = (skb->tail + delta) - skb->end;

	if (eat > 0 || skb_cloned(skb)) {
		if (pskb_expand_head(skb, 0, eat > 0 ? eat + 128 : 0,
				     GFP_ATOMIC))
			return NULL;
	}

	BUG_ON(skb_copy_bits(skb, skb_headlen(skb),
			     skb_tail_pointer(skb), delta));

	/* Optimization: no fragments, no reasons to preestimate
	 * size of pulled pages. Superb.
	 */
	if (!skb_has_frag_list(skb))
		goto pull_pages;

	/* Estimate size of pulled pages. */
	eat = delta;
	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		int size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		if (size >= eat)
			goto pull_pages;
		eat -= size;
	}

	/* If we need update frag list, we are in troubles.
	 * Certainly, it is possible to add an offset to skb data,
	 * but taking into account that pulling is expected to
	 * be very rare operation, it is worth to fight against
	 * further bloating skb head and crucify ourselves here instead.
	 * Pure masohism, indeed. 8)8)
	 */
	if (eat) {
		struct sk_buff *list = skb_shinfo(skb)->frag_list;
		struct sk_buff *clone = NULL;
		struct sk_buff *insp = NULL;

		do {
			if (list->len <= eat) {
				/* Eaten as whole. */
				eat -= list->len;
				list = list->next;
				insp = list;
			} else {
				/* Eaten partially. */

				if (skb_shared(list)) {
					/* Sucks! We need to fork list. :-( */
					clone = skb_clone(list, GFP_ATOMIC);
					if (!clone)
						return NULL;
					insp = list->next;
					list = clone;
				} else {
					/* This may be pulled without
					 * problems. */
					insp = list;
				}
				if (!pskb_pull(list, eat)) {
					kfree_skb(clone);
					return NULL;
				}
				break;
			}
		} while (eat);

		/* Free pulled out fragments. */
		while ((list = skb_shinfo(skb)->frag_list) != insp) {
			skb_shinfo(skb)->frag_list = list->next;
			kfree_skb(list);
		}
		/* And insert new clone at head. */
		if (clone) {
			clone->next = list;
			skb_shinfo(skb)->frag_list = clone;
		}
	}
	/* Success! Now we may commit changes to skb data. */

pull_pages:
	eat = delta;
	k = 0;
	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		int size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		if (size <= eat) {
			skb_frag_unref(skb, i);
			eat -= size;
		} else {
			skb_frag_t *frag = &skb_shinfo(skb)->frags[k];

			*frag = skb_shinfo(skb)->frags[i];
			if (eat) {
				skb_frag_off_add(frag, eat);
				skb_frag_size_sub(frag, eat);
				if (!i)
					goto end;
				eat = 0;
			}
			k++;
		}
	}
	skb_shinfo(skb)->nr_frags = k;

end:
	skb->tail     += delta;
	skb->data_len -= delta;

	if (!skb->data_len)
		skb_zcopy_clear(skb, false);

	return skb_tail_pointer(skb);
}