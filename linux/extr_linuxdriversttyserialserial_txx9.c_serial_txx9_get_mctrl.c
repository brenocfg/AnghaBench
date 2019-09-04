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
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  TXX9_SICISR ; 
 int TXX9_SICISR_CTSS ; 
 int /*<<< orphan*/  TXX9_SIFLCR ; 
 int TXX9_SIFLCR_RTSSC ; 
 int sio_in (struct uart_txx9_port*,int /*<<< orphan*/ ) ; 
 struct uart_txx9_port* to_uart_txx9_port (struct uart_port*) ; 

__attribute__((used)) static unsigned int serial_txx9_get_mctrl(struct uart_port *port)
{
	struct uart_txx9_port *up = to_uart_txx9_port(port);
	unsigned int ret;

	/* no modem control lines */
	ret = TIOCM_CAR | TIOCM_DSR;
	ret |= (sio_in(up, TXX9_SIFLCR) & TXX9_SIFLCR_RTSSC) ? 0 : TIOCM_RTS;
	ret |= (sio_in(up, TXX9_SICISR) & TXX9_SICISR_CTSS) ? 0 : TIOCM_CTS;

	return ret;
}