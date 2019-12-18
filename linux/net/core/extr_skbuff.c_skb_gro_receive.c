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
struct skb_shared_info {int nr_frags; struct sk_buff* frag_list; int /*<<< orphan*/ * frags; } ;
struct sk_buff {unsigned int len; unsigned int truesize; unsigned int data_len; unsigned char* data; struct sk_buff* next; int /*<<< orphan*/  head; scalar_t__ head_frag; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int same_flow; int /*<<< orphan*/  count; struct sk_buff* last; int /*<<< orphan*/  free; scalar_t__ flush; } ;

/* Variables and functions */
 int E2BIG ; 
 int MAX_SKB_FRAGS ; 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NAPI_GRO_FREE ; 
 int /*<<< orphan*/  NAPI_GRO_FREE_STOLEN_HEAD ; 
 unsigned int SKB_DATA_ALIGN (int) ; 
 unsigned int SKB_TRUESIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_frag_set_page (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  __skb_header_release (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  skb_end_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_frag_off_add (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_frag_size_sub (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int skb_gro_len (struct sk_buff*) ; 
 unsigned int skb_gro_offset (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (int /*<<< orphan*/ ) ; 

int skb_gro_receive(struct sk_buff *p, struct sk_buff *skb)
{
	struct skb_shared_info *pinfo, *skbinfo = skb_shinfo(skb);
	unsigned int offset = skb_gro_offset(skb);
	unsigned int headlen = skb_headlen(skb);
	unsigned int len = skb_gro_len(skb);
	unsigned int delta_truesize;
	struct sk_buff *lp;

	if (unlikely(p->len + len >= 65536 || NAPI_GRO_CB(skb)->flush))
		return -E2BIG;

	lp = NAPI_GRO_CB(p)->last;
	pinfo = skb_shinfo(lp);

	if (headlen <= offset) {
		skb_frag_t *frag;
		skb_frag_t *frag2;
		int i = skbinfo->nr_frags;
		int nr_frags = pinfo->nr_frags + i;

		if (nr_frags > MAX_SKB_FRAGS)
			goto merge;

		offset -= headlen;
		pinfo->nr_frags = nr_frags;
		skbinfo->nr_frags = 0;

		frag = pinfo->frags + nr_frags;
		frag2 = skbinfo->frags + i;
		do {
			*--frag = *--frag2;
		} while (--i);

		skb_frag_off_add(frag, offset);
		skb_frag_size_sub(frag, offset);

		/* all fragments truesize : remove (head size + sk_buff) */
		delta_truesize = skb->truesize -
				 SKB_TRUESIZE(skb_end_offset(skb));

		skb->truesize -= skb->data_len;
		skb->len -= skb->data_len;
		skb->data_len = 0;

		NAPI_GRO_CB(skb)->free = NAPI_GRO_FREE;
		goto done;
	} else if (skb->head_frag) {
		int nr_frags = pinfo->nr_frags;
		skb_frag_t *frag = pinfo->frags + nr_frags;
		struct page *page = virt_to_head_page(skb->head);
		unsigned int first_size = headlen - offset;
		unsigned int first_offset;

		if (nr_frags + 1 + skbinfo->nr_frags > MAX_SKB_FRAGS)
			goto merge;

		first_offset = skb->data -
			       (unsigned char *)page_address(page) +
			       offset;

		pinfo->nr_frags = nr_frags + 1 + skbinfo->nr_frags;

		__skb_frag_set_page(frag, page);
		skb_frag_off_set(frag, first_offset);
		skb_frag_size_set(frag, first_size);

		memcpy(frag + 1, skbinfo->frags, sizeof(*frag) * skbinfo->nr_frags);
		/* We dont need to clear skbinfo->nr_frags here */

		delta_truesize = skb->truesize - SKB_DATA_ALIGN(sizeof(struct sk_buff));
		NAPI_GRO_CB(skb)->free = NAPI_GRO_FREE_STOLEN_HEAD;
		goto done;
	}

merge:
	delta_truesize = skb->truesize;
	if (offset > headlen) {
		unsigned int eat = offset - headlen;

		skb_frag_off_add(&skbinfo->frags[0], eat);
		skb_frag_size_sub(&skbinfo->frags[0], eat);
		skb->data_len -= eat;
		skb->len -= eat;
		offset = headlen;
	}

	__skb_pull(skb, offset);

	if (NAPI_GRO_CB(p)->last == p)
		skb_shinfo(p)->frag_list = skb;
	else
		NAPI_GRO_CB(p)->last->next = skb;
	NAPI_GRO_CB(p)->last = skb;
	__skb_header_release(skb);
	lp = p;

done:
	NAPI_GRO_CB(p)->count++;
	p->data_len += len;
	p->truesize += delta_truesize;
	p->len += len;
	if (lp != p) {
		lp->data_len += len;
		lp->truesize += delta_truesize;
		lp->len += len;
	}
	NAPI_GRO_CB(skb)->same_flow = 1;
	return 0;
}