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
struct gsm_dlci {scalar_t__ addr; TYPE_1__* gsm; int /*<<< orphan*/  fifo; int /*<<< orphan*/  port; int /*<<< orphan*/  state; int /*<<< orphan*/  t1; } ;
struct TYPE_2__ {int dead; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLCI_CLOSED ; 
 int debug ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gsm_dlci_close(struct gsm_dlci *dlci)
{
	del_timer(&dlci->t1);
	if (debug & 8)
		pr_debug("DLCI %d goes closed.\n", dlci->addr);
	dlci->state = DLCI_CLOSED;
	if (dlci->addr != 0) {
		tty_port_tty_hangup(&dlci->port, false);
		kfifo_reset(dlci->fifo);
	} else
		dlci->gsm->dead = 1;
	wake_up(&dlci->gsm->event);
	/* A DLCI 0 close is a MUX termination so we need to kick that
	   back to userspace somehow */
}