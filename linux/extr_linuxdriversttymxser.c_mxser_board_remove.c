#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxser_board {int /*<<< orphan*/  irq; TYPE_2__* ports; scalar_t__ idx; TYPE_1__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct TYPE_3__ {unsigned int nports; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mxser_board*) ; 
 int /*<<< orphan*/  mxvar_sdriver ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxser_board_remove(struct mxser_board *brd)
{
	unsigned int i;

	for (i = 0; i < brd->info->nports; i++) {
		tty_unregister_device(mxvar_sdriver, brd->idx + i);
		tty_port_destroy(&brd->ports[i].port);
	}
	free_irq(brd->irq, brd);
}