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
struct sk_buff {int len; int data_len; int truesize; void* ip_summed; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* CHECKSUM_PARTIAL ; 
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  __skb_frag_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_frag_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_can_coalesce (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_off_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_off_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_size_sub (int /*<<< orphan*/ *,int) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_prepare_for_shift (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_zcopy (struct sk_buff*) ; 

int skb_shift(struct sk_buff *tgt, struct sk_buff *skb, int shiftlen)
{
	int from, to, merge, todo;
	skb_frag_t *fragfrom, *fragto;

	BUG_ON(shiftlen > skb->len);

	if (skb_headlen(skb))
		return 0;
	if (skb_zcopy(tgt) || skb_zcopy(skb))
		return 0;

	todo = shiftlen;
	from = 0;
	to = skb_shinfo(tgt)->nr_frags;
	fragfrom = &skb_shinfo(skb)->frags[from];

	/* Actual merge is delayed until the point when we know we can
	 * commit all, so that we don't have to undo partial changes
	 */
	if (!to ||
	    !skb_can_coalesce(tgt, to, skb_frag_page(fragfrom),
			      skb_frag_off(fragfrom))) {
		merge = -1;
	} else {
		merge = to - 1;

		todo -= skb_frag_size(fragfrom);
		if (todo < 0) {
			if (skb_prepare_for_shift(skb) ||
			    skb_prepare_for_shift(tgt))
				return 0;

			/* All previous frag pointers might be stale! */
			fragfrom = &skb_shinfo(skb)->frags[from];
			fragto = &skb_shinfo(tgt)->frags[merge];

			skb_frag_size_add(fragto, shiftlen);
			skb_frag_size_sub(fragfrom, shiftlen);
			skb_frag_off_add(fragfrom, shiftlen);

			goto onlymerged;
		}

		from++;
	}

	/* Skip full, not-fitting skb to avoid expensive operations */
	if ((shiftlen == skb->len) &&
	    (skb_shinfo(skb)->nr_frags - from) > (MAX_SKB_FRAGS - to))
		return 0;

	if (skb_prepare_for_shift(skb) || skb_prepare_for_shift(tgt))
		return 0;

	while ((todo > 0) && (from < skb_shinfo(skb)->nr_frags)) {
		if (to == MAX_SKB_FRAGS)
			return 0;

		fragfrom = &skb_shinfo(skb)->frags[from];
		fragto = &skb_shinfo(tgt)->frags[to];

		if (todo >= skb_frag_size(fragfrom)) {
			*fragto = *fragfrom;
			todo -= skb_frag_size(fragfrom);
			from++;
			to++;

		} else {
			__skb_frag_ref(fragfrom);
			skb_frag_page_copy(fragto, fragfrom);
			skb_frag_off_copy(fragto, fragfrom);
			skb_frag_size_set(fragto, todo);

			skb_frag_off_add(fragfrom, todo);
			skb_frag_size_sub(fragfrom, todo);
			todo = 0;

			to++;
			break;
		}
	}

	/* Ready to "commit" this state change to tgt */
	skb_shinfo(tgt)->nr_frags = to;

	if (merge >= 0) {
		fragfrom = &skb_shinfo(skb)->frags[0];
		fragto = &skb_shinfo(tgt)->frags[merge];

		skb_frag_size_add(fragto, skb_frag_size(fragfrom));
		__skb_frag_unref(fragfrom);
	}

	/* Reposition in the original skb */
	to = 0;
	while (from < skb_shinfo(skb)->nr_frags)
		skb_shinfo(skb)->frags[to++] = skb_shinfo(skb)->frags[from++];
	skb_shinfo(skb)->nr_frags = to;

	BUG_ON(todo > 0 && !skb_shinfo(skb)->nr_frags);

onlymerged:
	/* Most likely the tgt won't ever need its checksum anymore, skb on
	 * the other hand might need it if it needs to be resent
	 */
	tgt->ip_summed = CHECKSUM_PARTIAL;
	skb->ip_summed = CHECKSUM_PARTIAL;

	/* Yak, is it really working this way? Some helper please? */
	skb->len -= shiftlen;
	skb->data_len -= shiftlen;
	skb->truesize -= shiftlen;
	tgt->len += shiftlen;
	tgt->data_len += shiftlen;
	tgt->truesize += shiftlen;

	return shiftlen;
}