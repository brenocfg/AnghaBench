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
struct tty_struct {int /*<<< orphan*/  flags; scalar_t__ disc_data; } ;
struct nci_uart {struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nci_uart_tx_wakeup (struct nci_uart*) ; 

__attribute__((used)) static void nci_uart_tty_wakeup(struct tty_struct *tty)
{
	struct nci_uart *nu = (void *)tty->disc_data;

	if (!nu)
		return;

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	if (tty != nu->tty)
		return;

	nci_uart_tx_wakeup(nu);
}