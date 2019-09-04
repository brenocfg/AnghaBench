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
struct orc_host {int /*<<< orphan*/  allocation_lock; scalar_t__ base; } ;

/* Variables and functions */
 int FAILED ; 
 scalar_t__ ORC_HCTRL ; 
 int /*<<< orphan*/  SCSIRST ; 
 int SUCCESS ; 
 int /*<<< orphan*/  init_alloc_map (struct orc_host*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ wait_scsi_reset_done (struct orc_host*) ; 

__attribute__((used)) static int orc_reset_scsi_bus(struct orc_host * host)
{				/* I need Host Control Block Information */
	unsigned long flags;

	spin_lock_irqsave(&host->allocation_lock, flags);

	init_alloc_map(host);
	/* reset scsi bus */
	outb(SCSIRST, host->base + ORC_HCTRL);
	/* FIXME: We can spend up to a second with the lock held and
	   interrupts off here */
	if (wait_scsi_reset_done(host) == 0) {
		spin_unlock_irqrestore(&host->allocation_lock, flags);
		return FAILED;
	} else {
		spin_unlock_irqrestore(&host->allocation_lock, flags);
		return SUCCESS;
	}
}