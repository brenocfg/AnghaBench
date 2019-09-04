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
struct tun_file {int /*<<< orphan*/  napi; } ;
struct sk_buff {size_t len; size_t data_len; size_t truesize; } ;
struct page_frag {size_t offset; int /*<<< orphan*/  page; } ;
struct iov_iter {int nr_segs; TYPE_1__* iov; } ;
struct TYPE_4__ {struct page_frag task_frag; } ;
struct TYPE_3__ {size_t iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_SKB_FRAGS ; 
 size_t PAGE_SIZE ; 
 int __skb_grow (struct sk_buff*,size_t) ; 
 TYPE_2__* current ; 
 size_t iov_iter_single_seg_count (struct iov_iter const*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  napi_free_frags (int /*<<< orphan*/ *) ; 
 struct sk_buff* napi_get_frags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_ref_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  skb_page_frag_refill (size_t,struct page_frag*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *tun_napi_alloc_frags(struct tun_file *tfile,
					    size_t len,
					    const struct iov_iter *it)
{
	struct sk_buff *skb;
	size_t linear;
	int err;
	int i;

	if (it->nr_segs > MAX_SKB_FRAGS + 1)
		return ERR_PTR(-ENOMEM);

	local_bh_disable();
	skb = napi_get_frags(&tfile->napi);
	local_bh_enable();
	if (!skb)
		return ERR_PTR(-ENOMEM);

	linear = iov_iter_single_seg_count(it);
	err = __skb_grow(skb, linear);
	if (err)
		goto free;

	skb->len = len;
	skb->data_len = len - linear;
	skb->truesize += skb->data_len;

	for (i = 1; i < it->nr_segs; i++) {
		struct page_frag *pfrag = &current->task_frag;
		size_t fragsz = it->iov[i].iov_len;

		if (fragsz == 0 || fragsz > PAGE_SIZE) {
			err = -EINVAL;
			goto free;
		}

		if (!skb_page_frag_refill(fragsz, pfrag, GFP_KERNEL)) {
			err = -ENOMEM;
			goto free;
		}

		skb_fill_page_desc(skb, i - 1, pfrag->page,
				   pfrag->offset, fragsz);
		page_ref_inc(pfrag->page);
		pfrag->offset += fragsz;
	}

	return skb;
free:
	/* frees skb and all frags allocated with napi_alloc_frag() */
	napi_free_frags(&tfile->napi);
	return ERR_PTR(err);
}