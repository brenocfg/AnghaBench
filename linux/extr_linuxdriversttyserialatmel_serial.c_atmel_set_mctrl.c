#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_2__ {int flags; unsigned int delay_rts_after_send; } ;
struct uart_port {TYPE_1__ rs485; } ;
struct atmel_uart_port {int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 unsigned int ATMEL_US_CHMODE ; 
 unsigned int ATMEL_US_CHMODE_LOC_LOOP ; 
 unsigned int ATMEL_US_CHMODE_NORMAL ; 
 int /*<<< orphan*/  ATMEL_US_CR ; 
 unsigned int ATMEL_US_DTRDIS ; 
 unsigned int ATMEL_US_DTREN ; 
 int /*<<< orphan*/  ATMEL_US_MR ; 
 unsigned int ATMEL_US_RTSDIS ; 
 unsigned int ATMEL_US_RTSEN ; 
 int /*<<< orphan*/  ATMEL_US_TTGR ; 
 unsigned int ATMEL_US_USMODE ; 
 unsigned int ATMEL_US_USMODE_HWHS ; 
 unsigned int ATMEL_US_USMODE_RS485 ; 
 int SER_RS485_ENABLED ; 
 int TIOCM_DTR ; 
 int TIOCM_LOOP ; 
 int TIOCM_RTS ; 
 unsigned int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mctrl_gpio_set (int /*<<< orphan*/ ,int) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_set_mctrl(struct uart_port *port, u_int mctrl)
{
	unsigned int control = 0;
	unsigned int mode = atmel_uart_readl(port, ATMEL_US_MR);
	unsigned int rts_paused, rts_ready;
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	/* override mode to RS485 if needed, otherwise keep the current mode */
	if (port->rs485.flags & SER_RS485_ENABLED) {
		atmel_uart_writel(port, ATMEL_US_TTGR,
				  port->rs485.delay_rts_after_send);
		mode &= ~ATMEL_US_USMODE;
		mode |= ATMEL_US_USMODE_RS485;
	}

	/* set the RTS line state according to the mode */
	if ((mode & ATMEL_US_USMODE) == ATMEL_US_USMODE_HWHS) {
		/* force RTS line to high level */
		rts_paused = ATMEL_US_RTSEN;

		/* give the control of the RTS line back to the hardware */
		rts_ready = ATMEL_US_RTSDIS;
	} else {
		/* force RTS line to high level */
		rts_paused = ATMEL_US_RTSDIS;

		/* force RTS line to low level */
		rts_ready = ATMEL_US_RTSEN;
	}

	if (mctrl & TIOCM_RTS)
		control |= rts_ready;
	else
		control |= rts_paused;

	if (mctrl & TIOCM_DTR)
		control |= ATMEL_US_DTREN;
	else
		control |= ATMEL_US_DTRDIS;

	atmel_uart_writel(port, ATMEL_US_CR, control);

	mctrl_gpio_set(atmel_port->gpios, mctrl);

	/* Local loopback mode? */
	mode &= ~ATMEL_US_CHMODE;
	if (mctrl & TIOCM_LOOP)
		mode |= ATMEL_US_CHMODE_LOC_LOOP;
	else
		mode |= ATMEL_US_CHMODE_NORMAL;

	atmel_uart_writel(port, ATMEL_US_MR, mode);
}