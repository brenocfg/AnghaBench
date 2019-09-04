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
struct brcms_info {int /*<<< orphan*/  tx_flush_wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  tasklet; scalar_t__ resched; TYPE_1__* pub; int /*<<< orphan*/  wlc; int /*<<< orphan*/  isr_lock; } ;
struct TYPE_2__ {scalar_t__ up; } ;

/* Variables and functions */
 scalar_t__ brcms_c_dpc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_c_intrsupd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_intrson (struct brcms_info*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void brcms_dpc(unsigned long data)
{
	struct brcms_info *wl;

	wl = (struct brcms_info *) data;

	spin_lock_bh(&wl->lock);

	/* call the common second level interrupt handler */
	if (wl->pub->up) {
		if (wl->resched) {
			unsigned long flags;

			spin_lock_irqsave(&wl->isr_lock, flags);
			brcms_c_intrsupd(wl->wlc);
			spin_unlock_irqrestore(&wl->isr_lock, flags);
		}

		wl->resched = brcms_c_dpc(wl->wlc, true);
	}

	/* brcms_c_dpc() may bring the driver down */
	if (!wl->pub->up)
		goto done;

	/* re-schedule dpc */
	if (wl->resched)
		tasklet_schedule(&wl->tasklet);
	else
		/* re-enable interrupts */
		brcms_intrson(wl);

 done:
	spin_unlock_bh(&wl->lock);
	wake_up(&wl->tx_flush_wq);
}