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
typedef  int /*<<< orphan*/  u8 ;
struct page_frag {int offset; struct page* page; } ;
struct xfrm_state {int /*<<< orphan*/  lock; struct page_frag xfrag; } ;
struct sock {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {int len; int data_len; int truesize; struct sock* sk; } ;
struct page {int dummy; } ;
struct esp_info {int tailen; int inplace; int /*<<< orphan*/  proto; int /*<<< orphan*/  plen; int /*<<< orphan*/  tfclen; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  L1_CACHE_BYTES ; 
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  __skb_fill_page_desc (struct sk_buff*,int,struct page*,int,int) ; 
 int /*<<< orphan*/  esp_output_fill_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/ * kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pskb_put (struct sk_buff*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  refcount_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ sk_fullsock (struct sock*) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 int skb_cow_data (struct sk_buff*,int,struct sk_buff**) ; 
 int /*<<< orphan*/  skb_has_frag_list (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_page_frag_refill (int,struct page_frag*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_tail_pointer (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int esp6_output_head(struct xfrm_state *x, struct sk_buff *skb, struct esp_info *esp)
{
	u8 *tail;
	u8 *vaddr;
	int nfrags;
	struct page *page;
	struct sk_buff *trailer;
	int tailen = esp->tailen;

	if (!skb_cloned(skb)) {
		if (tailen <= skb_tailroom(skb)) {
			nfrags = 1;
			trailer = skb;
			tail = skb_tail_pointer(trailer);

			goto skip_cow;
		} else if ((skb_shinfo(skb)->nr_frags < MAX_SKB_FRAGS)
			   && !skb_has_frag_list(skb)) {
			int allocsize;
			struct sock *sk = skb->sk;
			struct page_frag *pfrag = &x->xfrag;

			esp->inplace = false;

			allocsize = ALIGN(tailen, L1_CACHE_BYTES);

			spin_lock_bh(&x->lock);

			if (unlikely(!skb_page_frag_refill(allocsize, pfrag, GFP_ATOMIC))) {
				spin_unlock_bh(&x->lock);
				goto cow;
			}

			page = pfrag->page;
			get_page(page);

			vaddr = kmap_atomic(page);

			tail = vaddr + pfrag->offset;

			esp_output_fill_trailer(tail, esp->tfclen, esp->plen, esp->proto);

			kunmap_atomic(vaddr);

			nfrags = skb_shinfo(skb)->nr_frags;

			__skb_fill_page_desc(skb, nfrags, page, pfrag->offset,
					     tailen);
			skb_shinfo(skb)->nr_frags = ++nfrags;

			pfrag->offset = pfrag->offset + allocsize;

			spin_unlock_bh(&x->lock);

			nfrags++;

			skb->len += tailen;
			skb->data_len += tailen;
			skb->truesize += tailen;
			if (sk && sk_fullsock(sk))
				refcount_add(tailen, &sk->sk_wmem_alloc);

			goto out;
		}
	}

cow:
	nfrags = skb_cow_data(skb, tailen, &trailer);
	if (nfrags < 0)
		goto out;
	tail = skb_tail_pointer(trailer);

skip_cow:
	esp_output_fill_trailer(tail, esp->tfclen, esp->plen, esp->proto);
	pskb_put(skb, trailer, tailen);

out:
	return nfrags;
}