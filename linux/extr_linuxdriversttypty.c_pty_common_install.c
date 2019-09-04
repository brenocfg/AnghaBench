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
struct tty_struct {int index; int /*<<< orphan*/  count; struct tty_port* port; struct tty_struct* link; int /*<<< orphan*/  termios; int /*<<< orphan*/  termios_locked; int /*<<< orphan*/  termios_rwsem; } ;
struct tty_port {struct tty_struct* itty; } ;
struct tty_driver {scalar_t__ subtype; int /*<<< orphan*/  owner; struct tty_driver* other; int /*<<< orphan*/  init_termios; struct tty_struct** ttys; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PTY_TYPE_MASTER ; 
 int /*<<< orphan*/  TTY_LOCK_SLAVE ; 
 struct tty_struct* alloc_tty_struct (struct tty_driver*,int) ; 
 int /*<<< orphan*/  kfree (struct tty_port*) ; 
 struct tty_port* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_buffer_set_limit (struct tty_port*,int) ; 
 int /*<<< orphan*/  tty_buffer_set_lock_subclass (struct tty_port*) ; 
 int /*<<< orphan*/  tty_driver_kref_get (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_init_termios (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_init (struct tty_port*) ; 
 int /*<<< orphan*/  tty_set_lock_subclass (struct tty_struct*) ; 

__attribute__((used)) static int pty_common_install(struct tty_driver *driver, struct tty_struct *tty,
		bool legacy)
{
	struct tty_struct *o_tty;
	struct tty_port *ports[2];
	int idx = tty->index;
	int retval = -ENOMEM;

	/* Opening the slave first has always returned -EIO */
	if (driver->subtype != PTY_TYPE_MASTER)
		return -EIO;

	ports[0] = kmalloc(sizeof **ports, GFP_KERNEL);
	ports[1] = kmalloc(sizeof **ports, GFP_KERNEL);
	if (!ports[0] || !ports[1])
		goto err;
	if (!try_module_get(driver->other->owner)) {
		/* This cannot in fact currently happen */
		goto err;
	}
	o_tty = alloc_tty_struct(driver->other, idx);
	if (!o_tty)
		goto err_put_module;

	tty_set_lock_subclass(o_tty);
	lockdep_set_subclass(&o_tty->termios_rwsem, TTY_LOCK_SLAVE);

	if (legacy) {
		/* We always use new tty termios data so we can do this
		   the easy way .. */
		tty_init_termios(tty);
		tty_init_termios(o_tty);

		driver->other->ttys[idx] = o_tty;
		driver->ttys[idx] = tty;
	} else {
		memset(&tty->termios_locked, 0, sizeof(tty->termios_locked));
		tty->termios = driver->init_termios;
		memset(&o_tty->termios_locked, 0, sizeof(tty->termios_locked));
		o_tty->termios = driver->other->init_termios;
	}

	/*
	 * Everything allocated ... set up the o_tty structure.
	 */
	tty_driver_kref_get(driver->other);
	/* Establish the links in both directions */
	tty->link   = o_tty;
	o_tty->link = tty;
	tty_port_init(ports[0]);
	tty_port_init(ports[1]);
	tty_buffer_set_limit(ports[0], 8192);
	tty_buffer_set_limit(ports[1], 8192);
	o_tty->port = ports[0];
	tty->port = ports[1];
	o_tty->port->itty = o_tty;

	tty_buffer_set_lock_subclass(o_tty->port);

	tty_driver_kref_get(driver);
	tty->count++;
	o_tty->count++;
	return 0;

err_put_module:
	module_put(driver->other->owner);
err:
	kfree(ports[0]);
	kfree(ports[1]);
	return retval;
}