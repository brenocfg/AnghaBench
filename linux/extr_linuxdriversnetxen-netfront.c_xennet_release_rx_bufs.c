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
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct netfront_queue {int* grant_rx_ref; int /*<<< orphan*/  rx_lock; struct sk_buff** rx_skbs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int GRANT_INVALID_REF ; 
 int NET_RX_RING_SIZE ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ page_address (struct page*) ; 
 struct page* skb_frag_page (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xennet_release_rx_bufs(struct netfront_queue *queue)
{
	int id, ref;

	spin_lock_bh(&queue->rx_lock);

	for (id = 0; id < NET_RX_RING_SIZE; id++) {
		struct sk_buff *skb;
		struct page *page;

		skb = queue->rx_skbs[id];
		if (!skb)
			continue;

		ref = queue->grant_rx_ref[id];
		if (ref == GRANT_INVALID_REF)
			continue;

		page = skb_frag_page(&skb_shinfo(skb)->frags[0]);

		/* gnttab_end_foreign_access() needs a page ref until
		 * foreign access is ended (which may be deferred).
		 */
		get_page(page);
		gnttab_end_foreign_access(ref, 0,
					  (unsigned long)page_address(page));
		queue->grant_rx_ref[id] = GRANT_INVALID_REF;

		kfree_skb(skb);
	}

	spin_unlock_bh(&queue->rx_lock);
}