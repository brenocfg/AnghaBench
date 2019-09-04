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
struct uart_port {int /*<<< orphan*/  membase; } ;

/* Variables and functions */
#define  UART_DLL_EM 135 
#define  UART_DLM_EM 134 
#define  UART_FCR 133 
#define  UART_IER 132 
#define  UART_LCR 131 
#define  UART_MCR 130 
#define  UART_SCR 129 
#define  UART_TX 128 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serial8250_em_serial_out(struct uart_port *p, int offset, int value)
{
	switch (offset) {
	case UART_TX: /* TX @ 0x00 */
		writeb(value, p->membase);
		break;
	case UART_FCR: /* FCR @ 0x0c (+1) */
	case UART_LCR: /* LCR @ 0x10 (+1) */
	case UART_MCR: /* MCR @ 0x14 (+1) */
	case UART_SCR: /* SCR @ 0x20 (+1) */
		writel(value, p->membase + ((offset + 1) << 2));
		break;
	case UART_IER: /* IER @ 0x04 */
		value &= 0x0f; /* only 4 valid bits - not Xscale */
		/* fall-through */
	case UART_DLL_EM: /* DLL @ 0x24 (+9) */
	case UART_DLM_EM: /* DLM @ 0x28 (+9) */
		writel(value, p->membase + (offset << 2));
	}
}