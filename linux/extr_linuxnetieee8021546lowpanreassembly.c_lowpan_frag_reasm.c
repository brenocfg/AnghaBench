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
struct sk_buff {int truesize; int /*<<< orphan*/  tstamp; struct net_device* dev; struct sk_buff* next; scalar_t__ len; scalar_t__ data_len; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct sk_buff* fragments_tail; struct sk_buff* fragments; int /*<<< orphan*/  stamp; int /*<<< orphan*/  net; } ;
struct lowpan_frag_queue {TYPE_2__ q; } ;
struct TYPE_3__ {int nr_frags; struct sk_buff* frag_list; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_frag_mem_limit (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  inet_frag_kill (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree_skb_partial (struct sk_buff*,int) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_list_init (struct sk_buff*) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_has_frag_list (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_morph (struct sk_buff*,struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_try_coalesce (struct sk_buff*,struct sk_buff*,int*,int*) ; 
 scalar_t__ skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sub_frag_mem_limit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lowpan_frag_reasm(struct lowpan_frag_queue *fq, struct sk_buff *prev,
			     struct net_device *ldev)
{
	struct sk_buff *fp, *head = fq->q.fragments;
	int sum_truesize;

	inet_frag_kill(&fq->q);

	/* Make the one we just received the head. */
	if (prev) {
		head = prev->next;
		fp = skb_clone(head, GFP_ATOMIC);

		if (!fp)
			goto out_oom;

		fp->next = head->next;
		if (!fp->next)
			fq->q.fragments_tail = fp;
		prev->next = fp;

		skb_morph(head, fq->q.fragments);
		head->next = fq->q.fragments->next;

		consume_skb(fq->q.fragments);
		fq->q.fragments = head;
	}

	/* Head of list must not be cloned. */
	if (skb_unclone(head, GFP_ATOMIC))
		goto out_oom;

	/* If the first fragment is fragmented itself, we split
	 * it to two chunks: the first with data and paged part
	 * and the second, holding only fragments.
	 */
	if (skb_has_frag_list(head)) {
		struct sk_buff *clone;
		int i, plen = 0;

		clone = alloc_skb(0, GFP_ATOMIC);
		if (!clone)
			goto out_oom;
		clone->next = head->next;
		head->next = clone;
		skb_shinfo(clone)->frag_list = skb_shinfo(head)->frag_list;
		skb_frag_list_init(head);
		for (i = 0; i < skb_shinfo(head)->nr_frags; i++)
			plen += skb_frag_size(&skb_shinfo(head)->frags[i]);
		clone->len = head->data_len - plen;
		clone->data_len = clone->len;
		head->data_len -= clone->len;
		head->len -= clone->len;
		add_frag_mem_limit(fq->q.net, clone->truesize);
	}

	WARN_ON(head == NULL);

	sum_truesize = head->truesize;
	for (fp = head->next; fp;) {
		bool headstolen;
		int delta;
		struct sk_buff *next = fp->next;

		sum_truesize += fp->truesize;
		if (skb_try_coalesce(head, fp, &headstolen, &delta)) {
			kfree_skb_partial(fp, headstolen);
		} else {
			if (!skb_shinfo(head)->frag_list)
				skb_shinfo(head)->frag_list = fp;
			head->data_len += fp->len;
			head->len += fp->len;
			head->truesize += fp->truesize;
		}
		fp = next;
	}
	sub_frag_mem_limit(fq->q.net, sum_truesize);

	head->next = NULL;
	head->dev = ldev;
	head->tstamp = fq->q.stamp;

	fq->q.fragments = NULL;
	fq->q.fragments_tail = NULL;

	return 1;
out_oom:
	net_dbg_ratelimited("lowpan_frag_reasm: no memory for reassembly\n");
	return -1;
}