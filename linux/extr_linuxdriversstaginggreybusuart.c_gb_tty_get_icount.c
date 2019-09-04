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
struct tty_struct {struct gb_tty* driver_data; } ;
struct serial_icounter_struct {int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; } ;
struct TYPE_2__ {int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; } ;
struct gb_tty {TYPE_1__ iocount; } ;

/* Variables and functions */

__attribute__((used)) static int gb_tty_get_icount(struct tty_struct *tty,
			     struct serial_icounter_struct *icount)
{
	struct gb_tty *gb_tty = tty->driver_data;

	icount->dsr = gb_tty->iocount.dsr;
	icount->rng = gb_tty->iocount.rng;
	icount->dcd = gb_tty->iocount.dcd;
	icount->frame = gb_tty->iocount.frame;
	icount->overrun = gb_tty->iocount.overrun;
	icount->parity = gb_tty->iocount.parity;
	icount->brk = gb_tty->iocount.brk;

	return 0;
}