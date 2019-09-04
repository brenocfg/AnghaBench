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
struct fnic {scalar_t__ state; int /*<<< orphan*/  fnic_lock; int /*<<< orphan*/  tx_queue; scalar_t__ in_remove; } ;
struct fc_lport {int dummy; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ FNIC_IN_ETH_MODE ; 
 scalar_t__ FNIC_IN_FC_MODE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int fnic_send_frame (struct fnic*,struct fc_frame*) ; 
 int /*<<< orphan*/  fp_skb (struct fc_frame*) ; 
 struct fnic* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int fnic_send(struct fc_lport *lp, struct fc_frame *fp)
{
	struct fnic *fnic = lport_priv(lp);
	unsigned long flags;

	if (fnic->in_remove) {
		dev_kfree_skb(fp_skb(fp));
		return -1;
	}

	/*
	 * Queue frame if in a transitional state.
	 * This occurs while registering the Port_ID / MAC address after FLOGI.
	 */
	spin_lock_irqsave(&fnic->fnic_lock, flags);
	if (fnic->state != FNIC_IN_FC_MODE && fnic->state != FNIC_IN_ETH_MODE) {
		skb_queue_tail(&fnic->tx_queue, fp_skb(fp));
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		return 0;
	}
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	return fnic_send_frame(fnic, fp);
}