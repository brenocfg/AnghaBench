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
 unsigned int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spinlock ; 
 int /*<<< orphan*/  testmode ; 
 int timeoutW ; 

__attribute__((used)) static int wdt_start(void)
{
	unsigned long flags;

	spin_lock_irqsave(&spinlock, flags);

	/* Unlock the SuperIO chip */
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);
	outb_p(UNLOCK_DATA, IO_INDEX_PORT);

	/*
	 * Select device Aux2 (device=8) to set watchdog regs F2, F3 and F4.
	 * F2 has the timeout in watchdog counter units.
	 * F3 is set to enable watchdog LED blink at timeout.
	 * F4 is used to just clear the TIMEOUT'ed state (bit 0).
	 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF2, IO_INDEX_PORT);
	outb_p(timeoutW, IO_DATA_PORT);
	outb_p(0xF3, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);
	outb_p(0xF4, IO_INDEX_PORT);
	outb_p(0x00, IO_DATA_PORT);

	/* Set device Aux2 active */
	outb_p(0x30, IO_INDEX_PORT);
	outb_p(0x01, IO_DATA_PORT);

	/*
	 * Select device Aux1 (dev=7) to set GP16 as the watchdog output
	 * (in reg E6) and GP13 as the watchdog LED output (in reg E3).
	 * Map GP16 at pin 119.
	 * In test mode watch the bit 0 on F4 to indicate "triggered" or
	 * check watchdog LED on SBC.
	 */
	outb_p(DEVICE_REGISTER, IO_INDEX_PORT);
	outb_p(0x07, IO_DATA_PORT);
	if (!testmode) {
		unsigned pin_map;

		outb_p(0xE6, IO_INDEX_PORT);
		outb_p(0x0A, IO_DATA_PORT);
		outb_p(0x2C, IO_INDEX_PORT);
		pin_map = inb_p(IO_DATA_PORT);
		pin_map |= 0x10;
		pin_map &= ~(0x20);
		outb_p(0x2C, IO_INDEX_PORT);
		outb_p(pin_map, IO_DATA_PORT);
	}
	outb_p(0xE3, IO_INDEX_PORT);
	outb_p(0x08, IO_DATA_PORT);

	/* Set device Aux1 active */
	outb_p(0x30, IO_INDEX_PORT);
	outb_p(0x01, IO_DATA_PORT);

	/* Lock the SuperIO chip */
	outb_p(LOCK_DATA, IO_INDEX_PORT);

	spin_unlock_irqrestore(&spinlock, flags);

	pr_info("activated\n");

	return 0;
}