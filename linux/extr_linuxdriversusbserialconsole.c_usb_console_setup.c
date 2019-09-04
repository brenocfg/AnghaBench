#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usbcons_info {struct usb_serial_port* port; } ;
struct TYPE_10__ {int console; scalar_t__ count; } ;
struct usb_serial_port {TYPE_4__ port; int /*<<< orphan*/  dev; struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  disc_mutex; int /*<<< orphan*/  interface; TYPE_1__* type; } ;
struct TYPE_9__ {int c_cflag; } ;
struct tty_struct {TYPE_3__ termios; int /*<<< orphan*/ * ops; TYPE_2__* driver; int /*<<< orphan*/  tty_files; int /*<<< orphan*/  files_lock; int /*<<< orphan*/  ldisc_sem; int /*<<< orphan*/  index; int /*<<< orphan*/  kref; } ;
struct ktermios {int dummy; } ;
struct console {int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  kref; } ;
struct TYPE_7__ {int (* open ) (int /*<<< orphan*/ *,struct usb_serial_port*) ;int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct usb_serial_port*,struct ktermios*) ;} ;

/* Variables and functions */
 int CLOCAL ; 
 int CREAD ; 
 int CS7 ; 
 int CS8 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HUPCL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_ldsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct tty_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int simple_strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_serial_port*) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*,struct usb_serial_port*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_init_termios (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_4__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_4__*,int) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_4__*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_save_termios (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (TYPE_3__*,int,int) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_console_fake_tty_ops ; 
 struct usb_serial_port* usb_serial_port_get_by_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_put (struct usb_serial*) ; 
 TYPE_2__* usb_serial_tty_driver ; 
 struct usbcons_info usbcons_info ; 

__attribute__((used)) static int usb_console_setup(struct console *co, char *options)
{
	struct usbcons_info *info = &usbcons_info;
	int baud = 9600;
	int bits = 8;
	int parity = 'n';
	int doflow = 0;
	int cflag = CREAD | HUPCL | CLOCAL;
	char *s;
	struct usb_serial *serial;
	struct usb_serial_port *port;
	int retval;
	struct tty_struct *tty = NULL;
	struct ktermios dummy;

	if (options) {
		baud = simple_strtoul(options, NULL, 10);
		s = options;
		while (*s >= '0' && *s <= '9')
			s++;
		if (*s)
			parity = *s++;
		if (*s)
			bits   = *s++ - '0';
		if (*s)
			doflow = (*s++ == 'r');
	}
	
	/* Sane default */
	if (baud == 0)
		baud = 9600;

	switch (bits) {
	case 7:
		cflag |= CS7;
		break;
	default:
	case 8:
		cflag |= CS8;
		break;
	}
	switch (parity) {
	case 'o': case 'O':
		cflag |= PARODD;
		break;
	case 'e': case 'E':
		cflag |= PARENB;
		break;
	}

	/*
	 * no need to check the index here: if the index is wrong, console
	 * code won't call us
	 */
	port = usb_serial_port_get_by_minor(co->index);
	if (port == NULL) {
		/* no device is connected yet, sorry :( */
		pr_err("No USB device connected to ttyUSB%i\n", co->index);
		return -ENODEV;
	}
	serial = port->serial;

	retval = usb_autopm_get_interface(serial->interface);
	if (retval)
		goto error_get_interface;

	tty_port_tty_set(&port->port, NULL);

	info->port = port;

	++port->port.count;
	if (!tty_port_initialized(&port->port)) {
		if (serial->type->set_termios) {
			/*
			 * allocate a fake tty so the driver can initialize
			 * the termios structure, then later call set_termios to
			 * configure according to command line arguments
			 */
			tty = kzalloc(sizeof(*tty), GFP_KERNEL);
			if (!tty) {
				retval = -ENOMEM;
				goto reset_open_count;
			}
			kref_init(&tty->kref);
			tty->driver = usb_serial_tty_driver;
			tty->index = co->index;
			init_ldsem(&tty->ldisc_sem);
			spin_lock_init(&tty->files_lock);
			INIT_LIST_HEAD(&tty->tty_files);
			kref_get(&tty->driver->kref);
			__module_get(tty->driver->owner);
			tty->ops = &usb_console_fake_tty_ops;
			tty_init_termios(tty);
			tty_port_tty_set(&port->port, tty);
		}

		/* only call the device specific open if this
		 * is the first time the port is opened */
		retval = serial->type->open(NULL, port);
		if (retval) {
			dev_err(&port->dev, "could not open USB console port\n");
			goto fail;
		}

		if (serial->type->set_termios) {
			tty->termios.c_cflag = cflag;
			tty_termios_encode_baud_rate(&tty->termios, baud, baud);
			memset(&dummy, 0, sizeof(struct ktermios));
			serial->type->set_termios(tty, port, &dummy);

			tty_port_tty_set(&port->port, NULL);
			tty_save_termios(tty);
			tty_kref_put(tty);
		}
		tty_port_set_initialized(&port->port, 1);
	}
	/* Now that any required fake tty operations are completed restore
	 * the tty port count */
	--port->port.count;
	/* The console is special in terms of closing the device so
	 * indicate this port is now acting as a system console. */
	port->port.console = 1;

	mutex_unlock(&serial->disc_mutex);
	return retval;

 fail:
	tty_port_tty_set(&port->port, NULL);
	tty_kref_put(tty);
 reset_open_count:
	port->port.count = 0;
	info->port = NULL;
	usb_autopm_put_interface(serial->interface);
 error_get_interface:
	usb_serial_put(serial);
	mutex_unlock(&serial->disc_mutex);
	return retval;
}