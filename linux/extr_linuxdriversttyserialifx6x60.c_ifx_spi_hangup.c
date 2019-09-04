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
struct tty_struct {struct ifx_spi_device* driver_data; } ;
struct ifx_spi_device {int /*<<< orphan*/  tty_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ifx_spi_hangup(struct tty_struct *tty)
{
	struct ifx_spi_device *ifx_dev = tty->driver_data;
	tty_port_hangup(&ifx_dev->tty_port);
}