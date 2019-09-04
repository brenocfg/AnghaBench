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
struct nci_uart {struct sk_buff* tx_skb; int /*<<< orphan*/  tx_q; } ;

/* Variables and functions */
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct sk_buff *nci_uart_dequeue(struct nci_uart *nu)
{
	struct sk_buff *skb = nu->tx_skb;

	if (!skb)
		skb = skb_dequeue(&nu->tx_q);
	else
		nu->tx_skb = NULL;

	return skb;
}