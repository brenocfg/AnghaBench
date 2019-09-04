#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct hso_serial* driver_data; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int count; } ;
struct hso_serial {scalar_t__ magic; TYPE_2__* parent; TYPE_1__ port; int /*<<< orphan*/  unthrottle_tasklet; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  minor; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  interface; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HSO_SERIAL_MAGIC ; 
 int /*<<< orphan*/  RX_IDLE ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _hso_serial_set_termios (struct tty_struct*,int /*<<< orphan*/ *) ; 
 struct hso_serial* get_serial_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hso_dbg (int,char*,...) ; 
 int /*<<< orphan*/  hso_serial_tiocmset (struct tty_struct*,int,int /*<<< orphan*/ ) ; 
 int hso_start_serial_device (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hso_stop_serial_device (TYPE_2__*) ; 
 scalar_t__ hso_unthrottle_tasklet ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,struct tty_struct*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_serial_open(struct tty_struct *tty, struct file *filp)
{
	struct hso_serial *serial = get_serial_by_index(tty->index);
	int result;

	/* sanity check */
	if (serial == NULL || serial->magic != HSO_SERIAL_MAGIC) {
		WARN_ON(1);
		tty->driver_data = NULL;
		hso_dbg(0x1, "Failed to open port\n");
		return -ENODEV;
	}

	mutex_lock(&serial->parent->mutex);
	result = usb_autopm_get_interface(serial->parent->interface);
	if (result < 0)
		goto err_out;

	hso_dbg(0x1, "Opening %d\n", serial->minor);

	/* setup */
	tty->driver_data = serial;
	tty_port_tty_set(&serial->port, tty);

	/* check for port already opened, if not set the termios */
	serial->port.count++;
	if (serial->port.count == 1) {
		serial->rx_state = RX_IDLE;
		/* Force default termio settings */
		_hso_serial_set_termios(tty, NULL);
		tasklet_init(&serial->unthrottle_tasklet,
			     (void (*)(unsigned long))hso_unthrottle_tasklet,
			     (unsigned long)serial);
		result = hso_start_serial_device(serial->parent, GFP_KERNEL);
		if (result) {
			hso_stop_serial_device(serial->parent);
			serial->port.count--;
		} else {
			kref_get(&serial->parent->ref);
		}
	} else {
		hso_dbg(0x1, "Port was already open\n");
	}

	usb_autopm_put_interface(serial->parent->interface);

	/* done */
	if (result)
		hso_serial_tiocmset(tty, TIOCM_RTS | TIOCM_DTR, 0);
err_out:
	mutex_unlock(&serial->parent->mutex);
	return result;
}