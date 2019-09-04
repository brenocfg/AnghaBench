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
typedef  int u8 ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F81534_FIFO_CONTROL_REG ; 
 int /*<<< orphan*/  F81534_LINE_STATUS_REG ; 
 int /*<<< orphan*/  F81534_MODEM_CONTROL_REG ; 
 int /*<<< orphan*/  F81534_MODEM_STATUS_REG ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_LSR_BI ; 
 int UART_MCR_LOOP ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DSR ; 
 int UART_MSR_RI ; 
 int f81534_get_phy_port_register (struct usb_serial*,int,int /*<<< orphan*/ ,int*) ; 
 int f81534_set_phy_port_register (struct usb_serial*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static bool f81534_check_port_hw_disabled(struct usb_serial *serial, int phy)
{
	int status;
	u8 old_mcr;
	u8 msr;
	u8 lsr;
	u8 msr_mask;

	msr_mask = UART_MSR_DCD | UART_MSR_RI | UART_MSR_DSR | UART_MSR_CTS;

	status = f81534_get_phy_port_register(serial, phy,
				F81534_MODEM_STATUS_REG, &msr);
	if (status)
		return false;

	if ((msr & msr_mask) != msr_mask)
		return false;

	status = f81534_set_phy_port_register(serial, phy,
				F81534_FIFO_CONTROL_REG, UART_FCR_ENABLE_FIFO |
				UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	if (status)
		return false;

	status = f81534_get_phy_port_register(serial, phy,
				F81534_MODEM_CONTROL_REG, &old_mcr);
	if (status)
		return false;

	status = f81534_set_phy_port_register(serial, phy,
				F81534_MODEM_CONTROL_REG, UART_MCR_LOOP);
	if (status)
		return false;

	status = f81534_set_phy_port_register(serial, phy,
				F81534_MODEM_CONTROL_REG, 0x0);
	if (status)
		return false;

	msleep(60);

	status = f81534_get_phy_port_register(serial, phy,
				F81534_LINE_STATUS_REG, &lsr);
	if (status)
		return false;

	status = f81534_set_phy_port_register(serial, phy,
				F81534_MODEM_CONTROL_REG, old_mcr);
	if (status)
		return false;

	if ((lsr & UART_LSR_BI) == UART_LSR_BI)
		return true;

	return false;
}