#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {struct hso_serial* driver_data; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct hso_serial {TYPE_2__* parent; int /*<<< orphan*/  unthrottle_tasklet; TYPE_1__ port; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  interface; int /*<<< orphan*/  usb_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  hso_dbg (int,char*) ; 
 int /*<<< orphan*/  hso_stop_serial_device (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hso_serial_close(struct tty_struct *tty, struct file *filp)
{
	struct hso_serial *serial = tty->driver_data;
	u8 usb_gone;

	hso_dbg(0x1, "Closing serial port\n");

	/* Open failed, no close cleanup required */
	if (serial == NULL)
		return;

	mutex_lock(&serial->parent->mutex);
	usb_gone = serial->parent->usb_gone;

	if (!usb_gone)
		usb_autopm_get_interface(serial->parent->interface);

	/* reset the rts and dtr */
	/* do the actual close */
	serial->port.count--;

	if (serial->port.count <= 0) {
		serial->port.count = 0;
		tty_port_tty_set(&serial->port, NULL);
		if (!usb_gone)
			hso_stop_serial_device(serial->parent);
		tasklet_kill(&serial->unthrottle_tasklet);
	}

	if (!usb_gone)
		usb_autopm_put_interface(serial->parent->interface);

	mutex_unlock(&serial->parent->mutex);
}