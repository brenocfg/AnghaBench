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
struct tty_driver {char* driver_name; char* name; int flags; int /*<<< orphan*/  init_termios; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SERIAL_TYPE_NORMAL ; 
 int TTY_DRIVER_DYNAMIC_DEV ; 
 int TTY_DRIVER_REAL_RAW ; 
 int TTY_DRIVER_RESET_TERMIOS ; 
 int /*<<< orphan*/  TTY_DRIVER_TYPE_SERIAL ; 
 struct tty_driver* alloc_tty_driver (int /*<<< orphan*/ ) ; 
 struct tty_driver* goldfish_tty_driver ; 
 int /*<<< orphan*/  goldfish_tty_line_count ; 
 int /*<<< orphan*/  goldfish_tty_ops ; 
 int /*<<< orphan*/ * goldfish_ttys ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_tty_driver (struct tty_driver*) ; 
 int tty_register_driver (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_set_operations (struct tty_driver*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_std_termios ; 

__attribute__((used)) static int goldfish_tty_create_driver(void)
{
	int ret;
	struct tty_driver *tty;

	goldfish_ttys = kcalloc(goldfish_tty_line_count,
				sizeof(*goldfish_ttys),
				GFP_KERNEL);
	if (goldfish_ttys == NULL) {
		ret = -ENOMEM;
		goto err_alloc_goldfish_ttys_failed;
	}
	tty = alloc_tty_driver(goldfish_tty_line_count);
	if (tty == NULL) {
		ret = -ENOMEM;
		goto err_alloc_tty_driver_failed;
	}
	tty->driver_name = "goldfish";
	tty->name = "ttyGF";
	tty->type = TTY_DRIVER_TYPE_SERIAL;
	tty->subtype = SERIAL_TYPE_NORMAL;
	tty->init_termios = tty_std_termios;
	tty->flags = TTY_DRIVER_RESET_TERMIOS | TTY_DRIVER_REAL_RAW |
						TTY_DRIVER_DYNAMIC_DEV;
	tty_set_operations(tty, &goldfish_tty_ops);
	ret = tty_register_driver(tty);
	if (ret)
		goto err_tty_register_driver_failed;

	goldfish_tty_driver = tty;
	return 0;

err_tty_register_driver_failed:
	put_tty_driver(tty);
err_alloc_tty_driver_failed:
	kfree(goldfish_ttys);
	goldfish_ttys = NULL;
err_alloc_goldfish_ttys_failed:
	return ret;
}