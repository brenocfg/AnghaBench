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
struct nci_uart {int /*<<< orphan*/  write_work; int /*<<< orphan*/  tx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_UART_SENDING ; 
 int /*<<< orphan*/  NCI_UART_TX_WAKEUP ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nci_uart_tx_wakeup(struct nci_uart *nu)
{
	if (test_and_set_bit(NCI_UART_SENDING, &nu->tx_state)) {
		set_bit(NCI_UART_TX_WAKEUP, &nu->tx_state);
		return 0;
	}

	schedule_work(&nu->write_work);

	return 0;
}