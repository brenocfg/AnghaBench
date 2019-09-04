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
typedef  int u64 ;
typedef  int u32 ;
typedef  int tcflag_t ;
struct uart_port {int uartclk; int /*<<< orphan*/  lock; TYPE_2__* dev; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct gpio_desc {int dummy; } ;
struct device_node {int /*<<< orphan*/  name; int /*<<< orphan*/  fwnode; } ;
struct TYPE_4__ {int read_status_mask; int ignore_status_mask; } ;
struct asc_port {TYPE_1__ port; int /*<<< orphan*/  force_m1; struct gpio_desc* rts; scalar_t__* states; int /*<<< orphan*/  pinctrl; int /*<<< orphan*/  clk; scalar_t__ hw_flow_control; } ;
struct TYPE_5__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_BAUDRATE ; 
 int /*<<< orphan*/  ASC_CTL ; 
 int ASC_CTL_BAUDMODE ; 
 int ASC_CTL_CTSENABLE ; 
 int ASC_CTL_FIFOENABLE ; 
 int ASC_CTL_MODE_7BIT_PAR ; 
 int ASC_CTL_MODE_8BIT ; 
 int ASC_CTL_MODE_8BIT_PAR ; 
 int ASC_CTL_PARITYODD ; 
 int ASC_CTL_RUN ; 
 int ASC_CTL_RXENABLE ; 
 int ASC_CTL_STOP_1BIT ; 
 int ASC_CTL_STOP_2BIT ; 
 int ASC_RXBUF_DUMMY_BE ; 
 int ASC_RXBUF_DUMMY_OE ; 
 int ASC_RXBUF_DUMMY_RX ; 
 int ASC_RXBUF_FE ; 
 int ASC_RXBUF_PE ; 
 int /*<<< orphan*/  ASC_RXRESET ; 
 int /*<<< orphan*/  ASC_TIMEOUT ; 
 int /*<<< orphan*/  ASC_TXRESET ; 
 int BRKINT ; 
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
 int CS7 ; 
 int CSIZE ; 
 int CSTOPB ; 
 size_t DEFAULT ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int /*<<< orphan*/  IS_ERR (struct gpio_desc*) ; 
 size_t NO_HW_FLOWCTRL ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int asc_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asc_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_fwnode_get_gpiod_from_child (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_put (TYPE_2__*,struct gpio_desc*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  pinctrl_select_state (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct asc_port* to_asc_port (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void asc_set_termios(struct uart_port *port, struct ktermios *termios,
			    struct ktermios *old)
{
	struct asc_port *ascport = to_asc_port(port);
	struct device_node *np = port->dev->of_node;
	struct gpio_desc *gpiod;
	unsigned int baud;
	u32 ctrl_val;
	tcflag_t cflag;
	unsigned long flags;

	/* Update termios to reflect hardware capabilities */
	termios->c_cflag &= ~(CMSPAR |
			 (ascport->hw_flow_control ? 0 : CRTSCTS));

	port->uartclk = clk_get_rate(ascport->clk);

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16);
	cflag = termios->c_cflag;

	spin_lock_irqsave(&port->lock, flags);

	/* read control register */
	ctrl_val = asc_in(port, ASC_CTL);

	/* stop serial port and reset value */
	asc_out(port, ASC_CTL, (ctrl_val & ~ASC_CTL_RUN));
	ctrl_val = ASC_CTL_RXENABLE | ASC_CTL_FIFOENABLE;

	/* reset fifo rx & tx */
	asc_out(port, ASC_TXRESET, 1);
	asc_out(port, ASC_RXRESET, 1);

	/* set character length */
	if ((cflag & CSIZE) == CS7) {
		ctrl_val |= ASC_CTL_MODE_7BIT_PAR;
	} else {
		ctrl_val |= (cflag & PARENB) ?  ASC_CTL_MODE_8BIT_PAR :
						ASC_CTL_MODE_8BIT;
	}

	/* set stop bit */
	ctrl_val |= (cflag & CSTOPB) ? ASC_CTL_STOP_2BIT : ASC_CTL_STOP_1BIT;

	/* odd parity */
	if (cflag & PARODD)
		ctrl_val |= ASC_CTL_PARITYODD;

	/* hardware flow control */
	if ((cflag & CRTSCTS)) {
		ctrl_val |= ASC_CTL_CTSENABLE;

		/* If flow-control selected, stop handling RTS manually */
		if (ascport->rts) {
			devm_gpiod_put(port->dev, ascport->rts);
			ascport->rts = NULL;

			pinctrl_select_state(ascport->pinctrl,
					     ascport->states[DEFAULT]);
		}
	} else {
		/* If flow-control disabled, it's safe to handle RTS manually */
		if (!ascport->rts && ascport->states[NO_HW_FLOWCTRL]) {
			pinctrl_select_state(ascport->pinctrl,
					     ascport->states[NO_HW_FLOWCTRL]);

			gpiod = devm_fwnode_get_gpiod_from_child(port->dev,
								 "rts",
								 &np->fwnode,
								 GPIOD_OUT_LOW,
								 np->name);
			if (!IS_ERR(gpiod))
				ascport->rts = gpiod;
		}
	}

	if ((baud < 19200) && !ascport->force_m1) {
		asc_out(port, ASC_BAUDRATE, (port->uartclk / (16 * baud)));
	} else {
		/*
		 * MODE 1: recommended for high bit rates (above 19.2K)
		 *
		 *                   baudrate * 16 * 2^16
		 * ASCBaudRate =   ------------------------
		 *                          inputclock
		 *
		 * To keep maths inside 64bits, we divide inputclock by 16.
		 */
		u64 dividend = (u64)baud * (1 << 16);

		do_div(dividend, port->uartclk / 16);
		asc_out(port, ASC_BAUDRATE, dividend);
		ctrl_val |= ASC_CTL_BAUDMODE;
	}

	uart_update_timeout(port, cflag, baud);

	ascport->port.read_status_mask = ASC_RXBUF_DUMMY_OE;
	if (termios->c_iflag & INPCK)
		ascport->port.read_status_mask |= ASC_RXBUF_FE | ASC_RXBUF_PE;
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		ascport->port.read_status_mask |= ASC_RXBUF_DUMMY_BE;

	/*
	 * Characters to ignore
	 */
	ascport->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		ascport->port.ignore_status_mask |= ASC_RXBUF_FE | ASC_RXBUF_PE;
	if (termios->c_iflag & IGNBRK) {
		ascport->port.ignore_status_mask |= ASC_RXBUF_DUMMY_BE;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			ascport->port.ignore_status_mask |= ASC_RXBUF_DUMMY_OE;
	}

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if (!(termios->c_cflag & CREAD))
		ascport->port.ignore_status_mask |= ASC_RXBUF_DUMMY_RX;

	/* Set the timeout */
	asc_out(port, ASC_TIMEOUT, 20);

	/* write final value and enable port */
	asc_out(port, ASC_CTL, (ctrl_val | ASC_CTL_RUN));

	spin_unlock_irqrestore(&port->lock, flags);
}