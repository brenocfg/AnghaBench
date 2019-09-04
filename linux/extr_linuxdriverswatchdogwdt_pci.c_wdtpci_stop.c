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

/* Variables and functions */
 int /*<<< orphan*/  WDT_DC ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wdtpci_ctr_load (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdtpci_lock ; 

__attribute__((used)) static int wdtpci_stop(void)
{
	unsigned long flags;

	/* Turn the card off */
	spin_lock_irqsave(&wdtpci_lock, flags);
	inb(WDT_DC);			/* Disable watchdog */
	udelay(8);
	wdtpci_ctr_load(2, 0);		/* 0 length reset pulses now */
	spin_unlock_irqrestore(&wdtpci_lock, flags);
	return 0;
}