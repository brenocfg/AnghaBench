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
typedef  void sk_buff ;
struct page {int dummy; } ;
struct bpf_test {int aux; int /*<<< orphan*/  frag_data; TYPE_1__* test; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_size; } ;

/* Variables and functions */
 int FLAG_NO_DATA ; 
 int FLAG_SKB_FRAG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_DATA ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (void*) ; 
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* populate_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_add_rx_frag (void*,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *generate_test_data(struct bpf_test *test, int sub)
{
	struct sk_buff *skb;
	struct page *page;

	if (test->aux & FLAG_NO_DATA)
		return NULL;

	/* Test case expects an skb, so populate one. Various
	 * subtests generate skbs of different sizes based on
	 * the same data.
	 */
	skb = populate_skb(test->data, test->test[sub].data_size);
	if (!skb)
		return NULL;

	if (test->aux & FLAG_SKB_FRAG) {
		/*
		 * when the test requires a fragmented skb, add a
		 * single fragment to the skb, filled with
		 * test->frag_data.
		 */
		void *ptr;

		page = alloc_page(GFP_KERNEL);

		if (!page)
			goto err_kfree_skb;

		ptr = kmap(page);
		if (!ptr)
			goto err_free_page;
		memcpy(ptr, test->frag_data, MAX_DATA);
		kunmap(page);
		skb_add_rx_frag(skb, 0, page, 0, MAX_DATA, MAX_DATA);
	}

	return skb;

err_free_page:
	__free_page(page);
err_kfree_skb:
	kfree_skb(skb);
	return NULL;
}