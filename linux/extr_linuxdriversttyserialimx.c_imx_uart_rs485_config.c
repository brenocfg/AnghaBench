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
typedef  int /*<<< orphan*/  u32 ;
struct serial_rs485 {int flags; scalar_t__ delay_rts_after_send; scalar_t__ delay_rts_before_send; } ;
struct uart_port {struct serial_rs485 rs485; } ;
struct imx_port {int /*<<< orphan*/  have_rtsgpio; scalar_t__ have_rtscts; } ;

/* Variables and functions */
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 int SER_RS485_RTS_ON_SEND ; 
 int SER_RS485_RX_DURING_TX ; 
 int /*<<< orphan*/  UCR2 ; 
 int /*<<< orphan*/  imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_rts_active (struct imx_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imx_uart_rts_inactive (struct imx_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imx_uart_start_rx (struct uart_port*) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_uart_rs485_config(struct uart_port *port,
				 struct serial_rs485 *rs485conf)
{
	struct imx_port *sport = (struct imx_port *)port;
	u32 ucr2;

	/* unimplemented */
	rs485conf->delay_rts_before_send = 0;
	rs485conf->delay_rts_after_send = 0;

	/* RTS is required to control the transmitter */
	if (!sport->have_rtscts && !sport->have_rtsgpio)
		rs485conf->flags &= ~SER_RS485_ENABLED;

	if (rs485conf->flags & SER_RS485_ENABLED) {
		/* Enable receiver if low-active RTS signal is requested */
		if (sport->have_rtscts &&  !sport->have_rtsgpio &&
		    !(rs485conf->flags & SER_RS485_RTS_ON_SEND))
			rs485conf->flags |= SER_RS485_RX_DURING_TX;

		/* disable transmitter */
		ucr2 = imx_uart_readl(sport, UCR2);
		if (rs485conf->flags & SER_RS485_RTS_AFTER_SEND)
			imx_uart_rts_active(sport, &ucr2);
		else
			imx_uart_rts_inactive(sport, &ucr2);
		imx_uart_writel(sport, ucr2, UCR2);
	}

	/* Make sure Rx is enabled in case Tx is active with Rx disabled */
	if (!(rs485conf->flags & SER_RS485_ENABLED) ||
	    rs485conf->flags & SER_RS485_RX_DURING_TX)
		imx_uart_start_rx(port);

	port->rs485 = *rs485conf;

	return 0;
}