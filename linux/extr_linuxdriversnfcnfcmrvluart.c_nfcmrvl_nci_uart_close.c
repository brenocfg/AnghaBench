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
struct nfcmrvl_private {int dummy; } ;
struct nci_uart {scalar_t__ drv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfcmrvl_nci_unregister_dev (struct nfcmrvl_private*) ; 

__attribute__((used)) static void nfcmrvl_nci_uart_close(struct nci_uart *nu)
{
	nfcmrvl_nci_unregister_dev((struct nfcmrvl_private *)nu->drv_data);
}