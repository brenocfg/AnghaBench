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
 int /*<<< orphan*/ * dbc_tty_driver ; 
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ *) ; 

void xhci_dbc_tty_unregister_driver(void)
{
	if (dbc_tty_driver) {
		tty_unregister_driver(dbc_tty_driver);
		put_tty_driver(dbc_tty_driver);
		dbc_tty_driver = NULL;
	}
}