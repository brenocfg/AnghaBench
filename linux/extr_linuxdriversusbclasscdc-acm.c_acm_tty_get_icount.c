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
struct tty_struct {struct acm* driver_data; } ;
struct serial_icounter_struct {int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; } ;
struct TYPE_2__ {int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; } ;
struct acm {TYPE_1__ iocount; } ;

/* Variables and functions */

__attribute__((used)) static int acm_tty_get_icount(struct tty_struct *tty,
					struct serial_icounter_struct *icount)
{
	struct acm *acm = tty->driver_data;

	icount->dsr = acm->iocount.dsr;
	icount->rng = acm->iocount.rng;
	icount->dcd = acm->iocount.dcd;
	icount->frame = acm->iocount.frame;
	icount->overrun = acm->iocount.overrun;
	icount->parity = acm->iocount.parity;
	icount->brk = acm->iocount.brk;

	return 0;
}