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
 int /*<<< orphan*/  KBD_DATA_REG ; 
 int /*<<< orphan*/  KBD_STATUS_REG ; 
 int KBD_STAT_MOUSE_OBF ; 
 int KBD_STAT_OBF ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inb (int /*<<< orphan*/ ) ; 
 scalar_t__ kbd_last_ret ; 

void kdb_kbd_cleanup_state(void)
{
	int scancode, scanstatus;

	/*
	 * Nothing to clean up, since either
	 * ENTER was never pressed, or has already
	 * gotten cleaned up.
	 */
	if (!kbd_last_ret)
		return;

	kbd_last_ret = 0;
	/*
	 * Enter key. Need to absorb the break code here, lest it gets
	 * leaked out if we exit KDB as the result of processing 'g'.
	 *
	 * This has several interesting implications:
	 * + Need to handle KP ENTER, which has break code 0xe0 0x9c.
	 * + Need to handle repeat ENTER and repeat KP ENTER. Repeats
	 *   only get a break code at the end of the repeated
	 *   sequence. This means we can't propagate the repeated key
	 *   press, and must swallow it away.
	 * + Need to handle possible PS/2 mouse input.
	 * + Need to handle mashed keys.
	 */

	while (1) {
		while ((inb(KBD_STATUS_REG) & KBD_STAT_OBF) == 0)
			cpu_relax();

		/*
		 * Fetch the scancode.
		 */
		scancode = inb(KBD_DATA_REG);
		scanstatus = inb(KBD_STATUS_REG);

		/*
		 * Skip mouse input.
		 */
		if (scanstatus & KBD_STAT_MOUSE_OBF)
			continue;

		/*
		 * If we see 0xe0, this is either a break code for KP
		 * ENTER, or a repeat make for KP ENTER. Either way,
		 * since the second byte is equivalent to an ENTER,
		 * skip the 0xe0 and try again.
		 *
		 * If we see 0x1c, this must be a repeat ENTER or KP
		 * ENTER (and we swallowed 0xe0 before). Try again.
		 *
		 * We can also see make and break codes for other keys
		 * mashed before or after pressing ENTER. Thus, if we
		 * see anything other than 0x9c, we have to try again.
		 *
		 * Note, if you held some key as ENTER was depressed,
		 * that break code would get leaked out.
		 */
		if (scancode != 0x9c)
			continue;

		return;
	}
}