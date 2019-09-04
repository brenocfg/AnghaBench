#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int len; unsigned long _skb_refdst; int /*<<< orphan*/  truesize; int /*<<< orphan*/  tstamp; struct net_device* dev; struct sk_buff* next; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int flags; int len; int meat; int /*<<< orphan*/  net; int /*<<< orphan*/  stamp; struct sk_buff* fragments; struct sk_buff* fragments_tail; } ;
struct lowpan_frag_queue {TYPE_1__ q; } ;
struct TYPE_4__ {int d_offset; int d_size; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int INET_FRAG_FIRST_IN ; 
 int INET_FRAG_LAST_IN ; 
 scalar_t__ LOWPAN_DISPATCH_FRAG1 ; 
 int /*<<< orphan*/  add_frag_mem_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_2__* lowpan_802154_cb (struct sk_buff*) ; 
 int lowpan_frag_reasm (struct lowpan_frag_queue*,struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static int lowpan_frag_queue(struct lowpan_frag_queue *fq,
			     struct sk_buff *skb, u8 frag_type)
{
	struct sk_buff *prev, *next;
	struct net_device *ldev;
	int end, offset;

	if (fq->q.flags & INET_FRAG_COMPLETE)
		goto err;

	offset = lowpan_802154_cb(skb)->d_offset << 3;
	end = lowpan_802154_cb(skb)->d_size;

	/* Is this the final fragment? */
	if (offset + skb->len == end) {
		/* If we already have some bits beyond end
		 * or have different end, the segment is corrupted.
		 */
		if (end < fq->q.len ||
		    ((fq->q.flags & INET_FRAG_LAST_IN) && end != fq->q.len))
			goto err;
		fq->q.flags |= INET_FRAG_LAST_IN;
		fq->q.len = end;
	} else {
		if (end > fq->q.len) {
			/* Some bits beyond end -> corruption. */
			if (fq->q.flags & INET_FRAG_LAST_IN)
				goto err;
			fq->q.len = end;
		}
	}

	/* Find out which fragments are in front and at the back of us
	 * in the chain of fragments so far.  We must know where to put
	 * this fragment, right?
	 */
	prev = fq->q.fragments_tail;
	if (!prev ||
	    lowpan_802154_cb(prev)->d_offset <
	    lowpan_802154_cb(skb)->d_offset) {
		next = NULL;
		goto found;
	}
	prev = NULL;
	for (next = fq->q.fragments; next != NULL; next = next->next) {
		if (lowpan_802154_cb(next)->d_offset >=
		    lowpan_802154_cb(skb)->d_offset)
			break;	/* bingo! */
		prev = next;
	}

found:
	/* Insert this fragment in the chain of fragments. */
	skb->next = next;
	if (!next)
		fq->q.fragments_tail = skb;
	if (prev)
		prev->next = skb;
	else
		fq->q.fragments = skb;

	ldev = skb->dev;
	if (ldev)
		skb->dev = NULL;

	fq->q.stamp = skb->tstamp;
	if (frag_type == LOWPAN_DISPATCH_FRAG1)
		fq->q.flags |= INET_FRAG_FIRST_IN;

	fq->q.meat += skb->len;
	add_frag_mem_limit(fq->q.net, skb->truesize);

	if (fq->q.flags == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    fq->q.meat == fq->q.len) {
		int res;
		unsigned long orefdst = skb->_skb_refdst;

		skb->_skb_refdst = 0UL;
		res = lowpan_frag_reasm(fq, prev, ldev);
		skb->_skb_refdst = orefdst;
		return res;
	}

	return -1;
err:
	kfree_skb(skb);
	return -1;
}