#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int c_cflag; int c_ispeed; int c_ospeed; } ;
struct TYPE_8__ {char* driver_name; char* name; int minor_start; int /*<<< orphan*/  major; int /*<<< orphan*/  flags; TYPE_1__ init_termios; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int B9600 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int ENOMEM ; 
 int HUPCL ; 
 int /*<<< orphan*/  SERIAL_TYPE_NORMAL ; 
 int /*<<< orphan*/  TTY_DRIVER_REAL_RAW ; 
 int /*<<< orphan*/  TTY_DRIVER_TYPE_SERIAL ; 
 TYPE_2__* alloc_tty_driver (int) ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  driver_version ; 
 int /*<<< orphan*/  mgsl_ops ; 
 int /*<<< orphan*/  printk (char*,char*,int,...) ; 
 int /*<<< orphan*/  put_tty_driver (TYPE_2__*) ; 
 TYPE_2__* serial_driver ; 
 int tty_register_driver (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_set_operations (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ tty_std_termios ; 
 int /*<<< orphan*/  ttymajor ; 

__attribute__((used)) static int mgsl_init_tty(void)
{
	int rc;

	serial_driver = alloc_tty_driver(128);
	if (!serial_driver)
		return -ENOMEM;
	
	serial_driver->driver_name = "synclink";
	serial_driver->name = "ttySL";
	serial_driver->major = ttymajor;
	serial_driver->minor_start = 64;
	serial_driver->type = TTY_DRIVER_TYPE_SERIAL;
	serial_driver->subtype = SERIAL_TYPE_NORMAL;
	serial_driver->init_termios = tty_std_termios;
	serial_driver->init_termios.c_cflag =
		B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	serial_driver->init_termios.c_ispeed = 9600;
	serial_driver->init_termios.c_ospeed = 9600;
	serial_driver->flags = TTY_DRIVER_REAL_RAW;
	tty_set_operations(serial_driver, &mgsl_ops);
	if ((rc = tty_register_driver(serial_driver)) < 0) {
		printk("%s(%d):Couldn't register serial driver\n",
			__FILE__,__LINE__);
		put_tty_driver(serial_driver);
		serial_driver = NULL;
		return rc;
	}
			
 	printk("%s %s, tty major#%d\n",
		driver_name, driver_version,
		serial_driver->major);
	return 0;
}