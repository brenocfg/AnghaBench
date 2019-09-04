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

/* Variables and functions */
 int nci_uart_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfcmrvl_nci_uart ; 

__attribute__((used)) static int nfcmrvl_uart_init_module(void)
{
	return nci_uart_register(&nfcmrvl_nci_uart);
}