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
 int DEVICE_REGISTER ; 
 int /*<<< orphan*/  IO_DATA_PORT ; 
 int /*<<< orphan*/  IO_INDEX_PORT ; 
 int LOCK_DATA ; 
 int UNLOCK_DATA ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spinlock ; 
 int timeoutM ; 

__attribute__((used)) static int wdt977_keepalive(void)
{
	unsigned long flags;
	spin_lock_irqsave(&spinlock, flags);

	/* unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* select device Aux2 (device=8) and kicks watchdog reg F2 */
	/* F2 has the timeout in minutes */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(timeoutM, IO_DATA_PORT);

	/* lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);
	spin_unlock_irqrestore(&spinlock, flags);

	return 0;
}