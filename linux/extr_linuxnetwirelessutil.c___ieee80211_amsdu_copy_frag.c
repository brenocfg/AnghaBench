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
struct skb_shared_info {int /*<<< orphan*/ * frags; } ;
struct sk_buff {int len; int data_len; void* data; int /*<<< orphan*/  head; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;

/* Variables and functions */
 int /*<<< orphan*/  __frame_add_frag (struct sk_buff*,struct page*,void*,int,int) ; 
 int min (int,int) ; 
 void* skb_frag_address (int /*<<< orphan*/  const*) ; 
 struct page* skb_frag_page (int /*<<< orphan*/  const*) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 struct page* virt_to_head_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__ieee80211_amsdu_copy_frag(struct sk_buff *skb, struct sk_buff *frame,
			    int offset, int len)
{
	struct skb_shared_info *sh = skb_shinfo(skb);
	const skb_frag_t *frag = &sh->frags[0];
	struct page *frag_page;
	void *frag_ptr;
	int frag_len, frag_size;
	int head_size = skb->len - skb->data_len;
	int cur_len;

	frag_page = virt_to_head_page(skb->head);
	frag_ptr = skb->data;
	frag_size = head_size;

	while (offset >= frag_size) {
		offset -= frag_size;
		frag_page = skb_frag_page(frag);
		frag_ptr = skb_frag_address(frag);
		frag_size = skb_frag_size(frag);
		frag++;
	}

	frag_ptr += offset;
	frag_len = frag_size - offset;

	cur_len = min(len, frag_len);

	__frame_add_frag(frame, frag_page, frag_ptr, cur_len, frag_size);
	len -= cur_len;

	while (len > 0) {
		frag_len = skb_frag_size(frag);
		cur_len = min(len, frag_len);
		__frame_add_frag(frame, skb_frag_page(frag),
				 skb_frag_address(frag), cur_len, frag_len);
		len -= cur_len;
		frag++;
	}
}