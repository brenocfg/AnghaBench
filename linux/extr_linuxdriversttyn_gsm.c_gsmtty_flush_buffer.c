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
struct tty_struct {struct gsm_dlci* driver_data; } ;
struct gsm_dlci {scalar_t__ state; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 scalar_t__ DLCI_CLOSED ; 
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsmtty_flush_buffer(struct tty_struct *tty)
{
	struct gsm_dlci *dlci = tty->driver_data;
	if (dlci->state == DLCI_CLOSED)
		return;
	/* Caution needed: If we implement reliable transport classes
	   then the data being transmitted can't simply be junked once
	   it has first hit the stack. Until then we can just blow it
	   away */
	kfifo_reset(dlci->fifo);
	/* Need to unhook this DLCI from the transmit queue logic */
}