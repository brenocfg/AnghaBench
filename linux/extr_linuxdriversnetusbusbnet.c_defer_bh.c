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
struct TYPE_2__ {int qlen; int /*<<< orphan*/  lock; } ;
struct usbnet {TYPE_1__ done; int /*<<< orphan*/  bh; } ;
struct skb_data {int state; } ;
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sk_buff {scalar_t__ cb; } ;
typedef  enum skb_state { ____Placeholder_skb_state } skb_state ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum skb_state defer_bh(struct usbnet *dev, struct sk_buff *skb,
		struct sk_buff_head *list, enum skb_state state)
{
	unsigned long		flags;
	enum skb_state 		old_state;
	struct skb_data *entry = (struct skb_data *) skb->cb;

	spin_lock_irqsave(&list->lock, flags);
	old_state = entry->state;
	entry->state = state;
	__skb_unlink(skb, list);

	/* defer_bh() is never called with list == &dev->done.
	 * spin_lock_nested() tells lockdep that it is OK to take
	 * dev->done.lock here with list->lock held.
	 */
	spin_lock_nested(&dev->done.lock, SINGLE_DEPTH_NESTING);

	__skb_queue_tail(&dev->done, skb);
	if (dev->done.qlen == 1)
		tasklet_schedule(&dev->bh);
	spin_unlock(&dev->done.lock);
	spin_unlock_irqrestore(&list->lock, flags);
	return old_state;
}