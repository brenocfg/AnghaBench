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
#define  UART_DLL_EM 136 
#define  UART_DLM_EM 135 
#define  UART_IER 134 
#define  UART_IIR 133 
#define  UART_LSR 132 
#define  UART_MCR 131 
#define  UART_MSR 130 
#define  UART_RX 129 
#define  UART_SCR 128 
 unsigned int readb (int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int serial8250_em_serial_in(struct uart_port *p, int offset)
{
	switch (offset) {
	case UART_RX: /* RX @ 0x00 */
		return readb(p->membase);
	case UART_MCR: /* MCR @ 0x14 (+1) */
	case UART_LSR: /* LSR @ 0x18 (+1) */
	case UART_MSR: /* MSR @ 0x1c (+1) */
	case UART_SCR: /* SCR @ 0x20 (+1) */
		return readl(p->membase + ((offset + 1) << 2));
	case UART_IER: /* IER @ 0x04 */
	case UART_IIR: /* IIR @ 0x08 */
	case UART_DLL_EM: /* DLL @ 0x24 (+9) */
	case UART_DLM_EM: /* DLM @ 0x28 (+9) */
		return readl(p->membase + (offset << 2));
	}
	return 0;
}