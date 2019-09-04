#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  init_termios; int /*<<< orphan*/  type; int /*<<< orphan*/  minor_start; int /*<<< orphan*/  name; int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  TTY_DRIVER_TYPE_SYSTEM ; 
 int /*<<< orphan*/  VCC_MAX_PORTS ; 
 int /*<<< orphan*/  VCC_MINOR_START ; 
 int /*<<< orphan*/  VCC_TTY_FLAGS ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_tty_driver (TYPE_1__*) ; 
 TYPE_1__* tty_alloc_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tty_register_driver (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_set_operations (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcc_device_node ; 
 int /*<<< orphan*/  vcc_driver_name ; 
 int /*<<< orphan*/  vcc_ops ; 
 TYPE_1__* vcc_tty_driver ; 
 int /*<<< orphan*/  vcc_tty_termios ; 
 int /*<<< orphan*/  vccdbg (char*) ; 
 int /*<<< orphan*/  version ; 

__attribute__((used)) static int vcc_tty_init(void)
{
	int rv;

	pr_info("VCC: %s\n", version);

	vcc_tty_driver = tty_alloc_driver(VCC_MAX_PORTS, VCC_TTY_FLAGS);
	if (IS_ERR(vcc_tty_driver)) {
		pr_err("VCC: TTY driver alloc failed\n");
		return PTR_ERR(vcc_tty_driver);
	}

	vcc_tty_driver->driver_name = vcc_driver_name;
	vcc_tty_driver->name = vcc_device_node;

	vcc_tty_driver->minor_start = VCC_MINOR_START;
	vcc_tty_driver->type = TTY_DRIVER_TYPE_SYSTEM;
	vcc_tty_driver->init_termios = vcc_tty_termios;

	tty_set_operations(vcc_tty_driver, &vcc_ops);

	rv = tty_register_driver(vcc_tty_driver);
	if (rv) {
		pr_err("VCC: TTY driver registration failed\n");
		put_tty_driver(vcc_tty_driver);
		vcc_tty_driver = NULL;
		return rv;
	}

	vccdbg("VCC: TTY driver registered\n");

	return 0;
}