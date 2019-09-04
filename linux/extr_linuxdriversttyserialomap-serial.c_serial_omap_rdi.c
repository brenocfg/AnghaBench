#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rx; } ;
struct TYPE_5__ {TYPE_1__ icount; } ;
struct uart_omap_port {TYPE_2__ port; } ;

/* Variables and functions */
 unsigned int TTY_NORMAL ; 
 unsigned int UART_LSR_DR ; 
 int /*<<< orphan*/  UART_LSR_OE ; 
 int /*<<< orphan*/  UART_RX ; 
 unsigned char serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_2__*,unsigned char) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_2__*,unsigned int,int /*<<< orphan*/ ,unsigned char,unsigned int) ; 

__attribute__((used)) static void serial_omap_rdi(struct uart_omap_port *up, unsigned int lsr)
{
	unsigned char ch = 0;
	unsigned int flag;

	if (!(lsr & UART_LSR_DR))
		return;

	ch = serial_in(up, UART_RX);
	flag = TTY_NORMAL;
	up->port.icount.rx++;

	if (uart_handle_sysrq_char(&up->port, ch))
		return;

	uart_insert_char(&up->port, lsr, UART_LSR_OE, ch, flag);
}