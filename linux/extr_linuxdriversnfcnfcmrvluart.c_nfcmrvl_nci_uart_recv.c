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
struct nfcmrvl_private {int dummy; } ;
struct nci_uart {scalar_t__ drv_data; } ;

/* Variables and functions */
 int nfcmrvl_nci_recv_frame (struct nfcmrvl_private*,struct sk_buff*) ; 

__attribute__((used)) static int nfcmrvl_nci_uart_recv(struct nci_uart *nu, struct sk_buff *skb)
{
	return nfcmrvl_nci_recv_frame((struct nfcmrvl_private *)nu->drv_data,
				      skb);
}