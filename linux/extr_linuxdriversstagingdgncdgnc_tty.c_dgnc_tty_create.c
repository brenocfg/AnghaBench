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
typedef  int /*<<< orphan*/  uint ;
struct TYPE_2__ {int c_cflag; int c_ispeed; int c_ospeed; } ;
struct tty_driver {char* name; int major; int minor_start; int /*<<< orphan*/  driver_name; TYPE_1__ init_termios; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; scalar_t__ name_base; } ;

/* Variables and functions */
 int B9600 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int /*<<< orphan*/  DRVSTR ; 
 struct tty_driver* ERR_PTR (int) ; 
 int HUPCL ; 
 scalar_t__ IS_ERR (struct tty_driver*) ; 
 int /*<<< orphan*/  SERIAL_TYPE_NORMAL ; 
 int TTY_DRIVER_DYNAMIC_DEV ; 
 int TTY_DRIVER_HARDWARE_BREAK ; 
 int TTY_DRIVER_REAL_RAW ; 
 int /*<<< orphan*/  TTY_DRIVER_TYPE_SERIAL ; 
 int /*<<< orphan*/  dgnc_tty_ops ; 
 int /*<<< orphan*/  put_tty_driver (struct tty_driver*) ; 
 struct tty_driver* tty_alloc_driver (int /*<<< orphan*/ ,int) ; 
 int tty_register_driver (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_set_operations (struct tty_driver*,int /*<<< orphan*/ *) ; 
 TYPE_1__ tty_std_termios ; 

__attribute__((used)) static struct tty_driver *dgnc_tty_create(char *serial_name, uint maxports,
					  int major, int minor)
{
	int rc;
	struct tty_driver *drv;

	drv = tty_alloc_driver(maxports,
			       TTY_DRIVER_REAL_RAW |
			       TTY_DRIVER_DYNAMIC_DEV |
			       TTY_DRIVER_HARDWARE_BREAK);
	if (IS_ERR(drv))
		return drv;

	drv->name = serial_name;
	drv->name_base = 0;
	drv->major = major;
	drv->minor_start = minor;
	drv->type = TTY_DRIVER_TYPE_SERIAL;
	drv->subtype = SERIAL_TYPE_NORMAL;
	drv->init_termios = tty_std_termios;
	drv->init_termios.c_cflag = (B9600 | CS8 | CREAD | HUPCL | CLOCAL);
	drv->init_termios.c_ispeed = 9600;
	drv->init_termios.c_ospeed = 9600;
	drv->driver_name = DRVSTR;
	/*
	 * Entry points for driver.  Called by the kernel from
	 * tty_io.c and n_tty.c.
	 */
	tty_set_operations(drv, &dgnc_tty_ops);
	rc = tty_register_driver(drv);
	if (rc < 0) {
		put_tty_driver(drv);
		return ERR_PTR(rc);
	}
	return drv;
}