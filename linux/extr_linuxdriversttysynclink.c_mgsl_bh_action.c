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
struct mgsl_struct {int pending_bh; int bh_running; int bh_requested; int /*<<< orphan*/  irq_spinlock; } ;

/* Variables and functions */
 int BH_RECEIVE ; 
 int BH_STATUS ; 
 int BH_TRANSMIT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mgsl_bh_action(struct mgsl_struct *info)
{
	unsigned long flags;
	int rc = 0;
	
	spin_lock_irqsave(&info->irq_spinlock,flags);

	if (info->pending_bh & BH_RECEIVE) {
		info->pending_bh &= ~BH_RECEIVE;
		rc = BH_RECEIVE;
	} else if (info->pending_bh & BH_TRANSMIT) {
		info->pending_bh &= ~BH_TRANSMIT;
		rc = BH_TRANSMIT;
	} else if (info->pending_bh & BH_STATUS) {
		info->pending_bh &= ~BH_STATUS;
		rc = BH_STATUS;
	}

	if (!rc) {
		/* Mark BH routine as complete */
		info->bh_running = false;
		info->bh_requested = false;
	}
	
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	
	return rc;
}