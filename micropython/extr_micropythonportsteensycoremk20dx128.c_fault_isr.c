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
 int SIM_SCGC4 ; 
 int SIM_SCGC4_UART0 ; 
 int SIM_SCGC4_UART1 ; 
 int SIM_SCGC4_UART2 ; 
 int SIM_SCGC4_USBOTG ; 
 int /*<<< orphan*/  uart0_status_isr () ; 
 int /*<<< orphan*/  uart1_status_isr () ; 
 int /*<<< orphan*/  uart2_status_isr () ; 
 int /*<<< orphan*/  usb_isr () ; 

void fault_isr(void)
{
	while (1) {
		// keep polling some communication while in fault
		// mode, so we don't completely die.
		if (SIM_SCGC4 & SIM_SCGC4_USBOTG) usb_isr();
		if (SIM_SCGC4 & SIM_SCGC4_UART0) uart0_status_isr();
		if (SIM_SCGC4 & SIM_SCGC4_UART1) uart1_status_isr();
		if (SIM_SCGC4 & SIM_SCGC4_UART2) uart2_status_isr();
	}
}