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
struct tty_struct {int /*<<< orphan*/  driver_data; } ;
struct qt2_port_private {int dummy; } ;

/* Variables and functions */
 int update_mctrl (struct qt2_port_private*,unsigned int,unsigned int) ; 
 struct qt2_port_private* usb_get_serial_port_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt2_tiocmset(struct tty_struct *tty,
			unsigned int set, unsigned int clear)
{
	struct qt2_port_private *port_priv;

	port_priv = usb_get_serial_port_data(tty->driver_data);
	return update_mctrl(port_priv, set, clear);
}