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
 int /*<<< orphan*/  IODEV_NO ; 
 int /*<<< orphan*/  close_io_config () ; 
 int /*<<< orphan*/  gpio_bit12 (int) ; 
 int /*<<< orphan*/  gpio_bit13 (int) ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  open_io_config () ; 
 int /*<<< orphan*/  select_io_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_timeout_value (int) ; 
 int /*<<< orphan*/  wdt_timer_conf (int) ; 
 int /*<<< orphan*/  wdt_timer_ctrl (int) ; 

__attribute__((used)) static void wb_smsc_wdt_shutdown(void)
{
	spin_lock(&io_lock);
	open_io_config();
	select_io_device(IODEV_NO);

	/* disable the watchdog */
	gpio_bit13(0x09);
	gpio_bit12(0x09);

	/* reset watchdog config register */
	wdt_timer_conf(0x00);

	/* reset watchdog control register */
	wdt_timer_ctrl(0x00);

	/* disable timeout */
	wdt_timeout_value(0x00);

	close_io_config();
	spin_unlock(&io_lock);
}