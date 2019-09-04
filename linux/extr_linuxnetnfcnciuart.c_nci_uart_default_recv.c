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
struct nci_uart {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int nci_recv_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int nci_uart_default_recv(struct nci_uart *nu, struct sk_buff *skb)
{
	return nci_recv_frame(nu->ndev, skb);
}