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
struct uart_port {int (* serial_in ) (struct uart_port*,int const) ;int regshift; scalar_t__ membase; } ;

/* Variables and functions */
#define  UART_FCR 130 
 int UART_FCR_UME ; 
#define  UART_IER 129 
 int UART_IER_MSI ; 
#define  UART_MCR 128 
 int UART_MCR_FCM ; 
 int UART_MCR_MDCE ; 
 int stub1 (struct uart_port*,int const) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void ingenic_uart_serial_out(struct uart_port *p, int offset, int value)
{
	int ier;

	switch (offset) {
	case UART_FCR:
		/* UART module enable */
		value |= UART_FCR_UME;
		break;

	case UART_IER:
		/*
		 * Enable receive timeout interrupt with the receive line
		 * status interrupt.
		 */
		value |= (value & 0x4) << 2;
		break;

	case UART_MCR:
		/*
		 * If we have enabled modem status IRQs we should enable
		 * modem mode.
		 */
		ier = p->serial_in(p, UART_IER);

		if (ier & UART_IER_MSI)
			value |= UART_MCR_MDCE | UART_MCR_FCM;
		else
			value &= ~(UART_MCR_MDCE | UART_MCR_FCM);
		break;

	default:
		break;
	}

	writeb(value, p->membase + (offset << p->regshift));
}