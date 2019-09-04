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
 int WDIOF_CARDRESET ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spinlock ; 

__attribute__((used)) static int wdt977_get_status(int *status)
{
	int new_status;
	unsigned long flags;

	spin_lock_irqsave(&spinlock, flags);

	/* unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/* select device Aux2 (device=8) and read watchdog reg F4 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF4, IO_INDEX_PORT);
	new_status = inb_p(IO_DATA_PORT);

	/* lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);

	*status = 0;
	if (new_status & 1)
		*status |= WDIOF_CARDRESET;

	return 0;
}