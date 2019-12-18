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
struct nci_uart {size_t driver; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** nci_uart_drivers ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,size_t) ; 

void nci_uart_unregister(struct nci_uart *nu)
{
	pr_info("NCI uart driver '%s [%d]' unregistered\n", nu->name,
		nu->driver);

	/* Remove this driver from the driver list */
	nci_uart_drivers[nu->driver] = NULL;
}