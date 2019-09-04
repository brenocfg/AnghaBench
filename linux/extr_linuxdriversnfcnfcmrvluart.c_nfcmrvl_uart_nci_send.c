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
struct sk_buff {int dummy; } ;
struct nfcmrvl_private {struct nci_uart* drv_data; } ;
struct TYPE_2__ {int (* send ) (struct nci_uart*,struct sk_buff*) ;} ;
struct nci_uart {TYPE_1__ ops; } ;

/* Variables and functions */
 int stub1 (struct nci_uart*,struct sk_buff*) ; 

__attribute__((used)) static int nfcmrvl_uart_nci_send(struct nfcmrvl_private *priv,
				 struct sk_buff *skb)
{
	struct nci_uart *nu = priv->drv_data;

	return nu->ops.send(nu, skb);
}