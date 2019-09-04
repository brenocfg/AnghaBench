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
 int /*<<< orphan*/  write_io_cr (int,unsigned char) ; 

__attribute__((used)) static inline void wdt_timer_units(unsigned char new_units)
{
	/* -- Watchdog timer units --
	 * Bit 0-6 (Reserved)
	 * Bit 7,  WDT Time-out Value Units Select
	 *         (0 = Minutes, 1 = Seconds)
	 */
	write_io_cr(0xF1, new_units);
}