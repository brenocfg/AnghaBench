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
struct sk_buff {int dummy; } ;
struct nci_uart {int /*<<< orphan*/  tx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  nci_uart_tx_wakeup (struct nci_uart*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int nci_uart_send(struct nci_uart *nu, struct sk_buff *skb)
{
	/* Queue TX packet */
	skb_queue_tail(&nu->tx_q, skb);

	/* Try to start TX (if possible) */
	nci_uart_tx_wakeup(nu);

	return 0;
}