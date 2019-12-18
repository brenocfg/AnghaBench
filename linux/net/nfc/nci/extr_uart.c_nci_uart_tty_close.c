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
struct tty_struct {int /*<<< orphan*/ * disc_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct nci_uart*) ;} ;
struct nci_uart {int /*<<< orphan*/  write_work; int /*<<< orphan*/  owner; int /*<<< orphan*/ * tty; TYPE_1__ ops; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nci_uart*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nci_uart*) ; 

__attribute__((used)) static void nci_uart_tty_close(struct tty_struct *tty)
{
	struct nci_uart *nu = (void *)tty->disc_data;

	/* Detach from the tty */
	tty->disc_data = NULL;

	if (!nu)
		return;

	kfree_skb(nu->tx_skb);
	kfree_skb(nu->rx_skb);

	skb_queue_purge(&nu->tx_q);

	nu->ops.close(nu);
	nu->tty = NULL;
	module_put(nu->owner);

	cancel_work_sync(&nu->write_work);

	kfree(nu);
}