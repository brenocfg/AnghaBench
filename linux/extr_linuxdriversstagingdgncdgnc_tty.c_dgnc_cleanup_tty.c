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
struct dgnc_board {int nasync; int /*<<< orphan*/  print_driver; int /*<<< orphan*/  serial_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ ) ; 

void dgnc_cleanup_tty(struct dgnc_board *brd)
{
	int i = 0;

	for (i = 0; i < brd->nasync; i++)
		tty_unregister_device(brd->serial_driver, i);

	tty_unregister_driver(brd->serial_driver);

	for (i = 0; i < brd->nasync; i++)
		tty_unregister_device(brd->print_driver, i);

	tty_unregister_driver(brd->print_driver);

	put_tty_driver(brd->serial_driver);
	put_tty_driver(brd->print_driver);
}