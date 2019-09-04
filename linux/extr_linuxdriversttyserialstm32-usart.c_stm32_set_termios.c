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
typedef  int u32 ;
typedef  int tcflag_t ;
struct serial_rs485 {int flags; int /*<<< orphan*/  delay_rts_after_send; int /*<<< orphan*/  delay_rts_before_send; } ;
struct uart_port {int uartclk; int status; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; scalar_t__ membase; struct serial_rs485 rs485; } ;
struct stm32_usart_offsets {scalar_t__ cr1; scalar_t__ cr2; scalar_t__ cr3; scalar_t__ brr; } ;
struct stm32_usart_config {int /*<<< orphan*/  uart_enable_bit; scalar_t__ has_7bits_data; } ;
struct stm32_port {scalar_t__ rx_ch; scalar_t__ fifoen; int /*<<< orphan*/  hw_flow_control; TYPE_1__* info; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct TYPE_2__ {struct stm32_usart_config cfg; struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int BRKINT ; 
 int CREAD ; 
 int CRTSCTS ; 
 int CS8 ; 
 int CSIZE ; 
 int CSTOPB ; 
 int DIV_ROUND_CLOSEST (int,unsigned int) ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 int SER_RS485_RTS_ON_SEND ; 
 int UPSTAT_AUTOCTS ; 
 int UPSTAT_AUTORTS ; 
 int USART_BRR_DIV_M_SHIFT ; 
 int USART_CR1_DEAT_MASK ; 
 int USART_CR1_DEDT_MASK ; 
 int USART_CR1_FIFOEN ; 
 int USART_CR1_M ; 
 int USART_CR1_M0 ; 
 int USART_CR1_OVER8 ; 
 int USART_CR1_PCE ; 
 int USART_CR1_PS ; 
 int USART_CR1_RE ; 
 int USART_CR1_RXNEIE ; 
 int USART_CR1_TE ; 
 int USART_CR2_STOP_2B ; 
 int USART_CR3_CTSE ; 
 int USART_CR3_DEM ; 
 int USART_CR3_DEP ; 
 int USART_CR3_DMAR ; 
 int USART_CR3_RTSE ; 
 int USART_SR_DUMMY_RX ; 
 int USART_SR_FE ; 
 int USART_SR_LBD ; 
 int USART_SR_ORE ; 
 int USART_SR_PE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,scalar_t__,int) ; 
 int /*<<< orphan*/  stm32_config_reg_rs485 (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stm32_set_bits (struct uart_port*,scalar_t__,int) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32_set_termios(struct uart_port *port, struct ktermios *termios,
			    struct ktermios *old)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	struct stm32_usart_config *cfg = &stm32_port->info->cfg;
	struct serial_rs485 *rs485conf = &port->rs485;
	unsigned int baud;
	u32 usartdiv, mantissa, fraction, oversampling;
	tcflag_t cflag = termios->c_cflag;
	u32 cr1, cr2, cr3;
	unsigned long flags;

	if (!stm32_port->hw_flow_control)
		cflag &= ~CRTSCTS;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 8);

	spin_lock_irqsave(&port->lock, flags);

	/* Stop serial port and reset value */
	writel_relaxed(0, port->membase + ofs->cr1);

	cr1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

	if (stm32_port->fifoen)
		cr1 |= USART_CR1_FIFOEN;
	cr2 = 0;
	cr3 = 0;

	if (cflag & CSTOPB)
		cr2 |= USART_CR2_STOP_2B;

	if (cflag & PARENB) {
		cr1 |= USART_CR1_PCE;
		if ((cflag & CSIZE) == CS8) {
			if (cfg->has_7bits_data)
				cr1 |= USART_CR1_M0;
			else
				cr1 |= USART_CR1_M;
		}
	}

	if (cflag & PARODD)
		cr1 |= USART_CR1_PS;

	port->status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS);
	if (cflag & CRTSCTS) {
		port->status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		cr3 |= USART_CR3_CTSE | USART_CR3_RTSE;
	}

	usartdiv = DIV_ROUND_CLOSEST(port->uartclk, baud);

	/*
	 * The USART supports 16 or 8 times oversampling.
	 * By default we prefer 16 times oversampling, so that the receiver
	 * has a better tolerance to clock deviations.
	 * 8 times oversampling is only used to achieve higher speeds.
	 */
	if (usartdiv < 16) {
		oversampling = 8;
		cr1 |= USART_CR1_OVER8;
		stm32_set_bits(port, ofs->cr1, USART_CR1_OVER8);
	} else {
		oversampling = 16;
		cr1 &= ~USART_CR1_OVER8;
		stm32_clr_bits(port, ofs->cr1, USART_CR1_OVER8);
	}

	mantissa = (usartdiv / oversampling) << USART_BRR_DIV_M_SHIFT;
	fraction = usartdiv % oversampling;
	writel_relaxed(mantissa | fraction, port->membase + ofs->brr);

	uart_update_timeout(port, cflag, baud);

	port->read_status_mask = USART_SR_ORE;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= USART_SR_PE | USART_SR_FE;
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= USART_SR_LBD;

	/* Characters to ignore */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask = USART_SR_PE | USART_SR_FE;
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= USART_SR_LBD;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= USART_SR_ORE;
	}

	/* Ignore all characters if CREAD is not set */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= USART_SR_DUMMY_RX;

	if (stm32_port->rx_ch)
		cr3 |= USART_CR3_DMAR;

	if (rs485conf->flags & SER_RS485_ENABLED) {
		stm32_config_reg_rs485(&cr1, &cr3,
				       rs485conf->delay_rts_before_send,
				       rs485conf->delay_rts_after_send, baud);
		if (rs485conf->flags & SER_RS485_RTS_ON_SEND) {
			cr3 &= ~USART_CR3_DEP;
			rs485conf->flags &= ~SER_RS485_RTS_AFTER_SEND;
		} else {
			cr3 |= USART_CR3_DEP;
			rs485conf->flags |= SER_RS485_RTS_AFTER_SEND;
		}

	} else {
		cr3 &= ~(USART_CR3_DEM | USART_CR3_DEP);
		cr1 &= ~(USART_CR1_DEDT_MASK | USART_CR1_DEAT_MASK);
	}

	writel_relaxed(cr3, port->membase + ofs->cr3);
	writel_relaxed(cr2, port->membase + ofs->cr2);
	writel_relaxed(cr1, port->membase + ofs->cr1);

	stm32_set_bits(port, ofs->cr1, BIT(cfg->uart_enable_bit));
	spin_unlock_irqrestore(&port->lock, flags);
}