#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rtllib_txb {unsigned int queue_index; int nr_frags; TYPE_2__** fragments; } ;
struct TYPE_5__ {int /*<<< orphan*/  multicast; } ;
struct rtllib_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  rate; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * skb_waitQ; scalar_t__ queue_stop; int /*<<< orphan*/  (* check_nic_enough_desc ) (int /*<<< orphan*/ ,unsigned int) ;TYPE_1__ stats; } ;
struct cb_desc {scalar_t__ bMulticast; } ;
struct TYPE_6__ {scalar_t__ cb; } ;

/* Variables and functions */
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 int /*<<< orphan*/  kfree_skb (TYPE_2__*) ; 
 int /*<<< orphan*/  rtllib_sta_wakeup (struct rtllib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtllib_txb_free (struct rtllib_txb*) ; 
 unsigned long skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtllib_softmac_xmit(struct rtllib_txb *txb, struct rtllib_device *ieee)
{

	unsigned int queue_index = txb->queue_index;
	unsigned long flags;
	int  i;
	struct cb_desc *tcb_desc = NULL;
	unsigned long queue_len = 0;

	spin_lock_irqsave(&ieee->lock, flags);

	/* called with 2nd parm 0, no tx mgmt lock required */
	rtllib_sta_wakeup(ieee, 0);

	/* update the tx status */
	tcb_desc = (struct cb_desc *)(txb->fragments[0]->cb +
		   MAX_DEV_ADDR_SIZE);
	if (tcb_desc->bMulticast)
		ieee->stats.multicast++;

	/* if xmit available, just xmit it immediately, else just insert it to
	 * the wait queue
	 */
	for (i = 0; i < txb->nr_frags; i++) {
		queue_len = skb_queue_len(&ieee->skb_waitQ[queue_index]);
		if ((queue_len  != 0) ||
		    (!ieee->check_nic_enough_desc(ieee->dev, queue_index)) ||
		    (ieee->queue_stop)) {
			/* insert the skb packet to the wait queue
			 * as for the completion function, it does not need
			 * to check it any more.
			 */
			if (queue_len < 200)
				skb_queue_tail(&ieee->skb_waitQ[queue_index],
					       txb->fragments[i]);
			else
				kfree_skb(txb->fragments[i]);
		} else {
			ieee->softmac_data_hard_start_xmit(
					txb->fragments[i],
					ieee->dev, ieee->rate);
		}
	}

	rtllib_txb_free(txb);

	spin_unlock_irqrestore(&ieee->lock, flags);

}