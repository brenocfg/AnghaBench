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
struct urb {scalar_t__ actual_length; } ;
struct list_head {int dummy; } ;
struct rx_agg {struct list_head list; struct urb* urb; } ;
struct r8152 {int /*<<< orphan*/  rx_lock; struct list_head rx_done; struct rx_agg* rx_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int RTL8152_MAX_RX ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice_tail (struct list_head*,struct list_head*) ; 
 int r8152_submit_rx (struct r8152*,struct rx_agg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rtl_start_rx(struct r8152 *tp)
{
	int i, ret = 0;

	INIT_LIST_HEAD(&tp->rx_done);
	for (i = 0; i < RTL8152_MAX_RX; i++) {
		INIT_LIST_HEAD(&tp->rx_info[i].list);
		ret = r8152_submit_rx(tp, &tp->rx_info[i], GFP_KERNEL);
		if (ret)
			break;
	}

	if (ret && ++i < RTL8152_MAX_RX) {
		struct list_head rx_queue;
		unsigned long flags;

		INIT_LIST_HEAD(&rx_queue);

		do {
			struct rx_agg *agg = &tp->rx_info[i++];
			struct urb *urb = agg->urb;

			urb->actual_length = 0;
			list_add_tail(&agg->list, &rx_queue);
		} while (i < RTL8152_MAX_RX);

		spin_lock_irqsave(&tp->rx_lock, flags);
		list_splice_tail(&rx_queue, &tp->rx_done);
		spin_unlock_irqrestore(&tp->rx_lock, flags);
	}

	return ret;
}