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
struct nci_uart {int /*<<< orphan*/  tx_q; scalar_t__ tx_skb; } ;

/* Variables and functions */
 int skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int nci_uart_queue_empty(struct nci_uart *nu)
{
	if (nu->tx_skb)
		return 0;

	return skb_queue_empty(&nu->tx_q);
}