#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {size_t index; TYPE_1__* driver_data; } ;
struct tty_driver {struct mips_ejtag_fdc_tty* driver_state; } ;
struct mips_ejtag_fdc_tty {TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int tty_port_install (int /*<<< orphan*/ *,struct tty_driver*,struct tty_struct*) ; 

__attribute__((used)) static int mips_ejtag_fdc_tty_install(struct tty_driver *driver,
				      struct tty_struct *tty)
{
	struct mips_ejtag_fdc_tty *priv = driver->driver_state;

	tty->driver_data = &priv->ports[tty->index];
	return tty_port_install(&priv->ports[tty->index].port, driver, tty);
}