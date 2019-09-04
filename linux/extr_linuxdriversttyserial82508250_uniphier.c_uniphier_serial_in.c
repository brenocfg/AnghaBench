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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
#define  UART_LCR 130 
#define  UART_MCR 129 
#define  UART_SCR 128 
 int UNIPHIER_UART_CHAR_FCR ; 
 int UNIPHIER_UART_LCR_MCR ; 
 int UNIPHIER_UART_REGSHIFT ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int uniphier_serial_in(struct uart_port *p, int offset)
{
	unsigned int valshift = 0;

	switch (offset) {
	case UART_SCR:
		/* No SCR for this hardware.  Use CHAR as a scratch register */
		valshift = 8;
		offset = UNIPHIER_UART_CHAR_FCR;
		break;
	case UART_LCR:
		valshift = 8;
		/* fall through */
	case UART_MCR:
		offset = UNIPHIER_UART_LCR_MCR;
		break;
	default:
		offset <<= UNIPHIER_UART_REGSHIFT;
		break;
	}

	/*
	 * The return value must be masked with 0xff because some registers
	 * share the same offset that must be accessed by 32-bit write/read.
	 * 8 or 16 bit access to this hardware result in unexpected behavior.
	 */
	return (readl(p->membase + offset) >> valshift) & 0xff;
}