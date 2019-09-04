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
struct dgnc_board {int /*<<< orphan*/  serial_driver; int /*<<< orphan*/  print_driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  dgnc_tty_free (int /*<<< orphan*/ ) ; 

void dgnc_tty_unregister(struct dgnc_board *brd)
{
	dgnc_tty_free(brd->print_driver);
	dgnc_tty_free(brd->serial_driver);
}