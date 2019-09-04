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
struct uart_txx9_port {int dummy; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  TXX9_SIFLCR ; 
 int /*<<< orphan*/  TXX9_SIFLCR_RTSSC ; 
 int /*<<< orphan*/  sio_mask (struct uart_txx9_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_set (struct uart_txx9_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uart_txx9_port* to_uart_txx9_port (struct uart_port*) ; 

__attribute__((used)) static void serial_txx9_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct uart_txx9_port *up = to_uart_txx9_port(port);

	if (mctrl & TIOCM_RTS)
		sio_mask(up, TXX9_SIFLCR, TXX9_SIFLCR_RTSSC);
	else
		sio_set(up, TXX9_SIFLCR, TXX9_SIFLCR_RTSSC);
}