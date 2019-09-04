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
struct uart_omap_port {int fcr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_DR ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_OMAP_MDR1 ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,int) ; 
 int serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void serial_omap_mdr1_errataset(struct uart_omap_port *up, u8 mdr1)
{
	u8 timeout = 255;

	serial_out(up, UART_OMAP_MDR1, mdr1);
	udelay(2);
	serial_out(up, UART_FCR, up->fcr | UART_FCR_CLEAR_XMIT |
			UART_FCR_CLEAR_RCVR);
	/*
	 * Wait for FIFO to empty: when empty, RX_FIFO_E bit is 0 and
	 * TX_FIFO_E bit is 1.
	 */
	while (UART_LSR_THRE != (serial_in(up, UART_LSR) &
				(UART_LSR_THRE | UART_LSR_DR))) {
		timeout--;
		if (!timeout) {
			/* Should *never* happen. we warn and carry on */
			dev_crit(up->dev, "Errata i202: timedout %x\n",
						serial_in(up, UART_LSR));
			break;
		}
		udelay(1);
	}
}