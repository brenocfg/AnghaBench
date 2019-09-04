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
 int gb_gbphy_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_tty_exit () ; 
 int gb_tty_init () ; 
 int /*<<< orphan*/  uart_driver ; 

__attribute__((used)) static int gb_uart_driver_init(void)
{
	int ret;

	ret = gb_tty_init();
	if (ret)
		return ret;

	ret = gb_gbphy_register(&uart_driver);
	if (ret) {
		gb_tty_exit();
		return ret;
	}

	return 0;
}