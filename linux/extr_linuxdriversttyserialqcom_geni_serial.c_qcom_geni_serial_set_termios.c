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
struct uart_port {unsigned long uartclk; scalar_t__ membase; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;
struct qcom_geni_serial_port {unsigned int baud; unsigned long loopback; TYPE_1__ se; } ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
 unsigned int CLK_DIV_SHFT ; 
 int CMSPAR ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 scalar_t__ GENI_SER_M_CLK_CFG ; 
 scalar_t__ GENI_SER_S_CLK_CFG ; 
 int PARENB ; 
 int PARODD ; 
 unsigned int PAR_CALC_EN ; 
 unsigned int PAR_EVEN ; 
 unsigned int PAR_ODD ; 
 unsigned int PAR_SPACE ; 
 unsigned long SER_CLK_EN ; 
 scalar_t__ SE_UART_LOOPBACK_CFG ; 
 scalar_t__ SE_UART_RX_PARITY_CFG ; 
 scalar_t__ SE_UART_RX_TRANS_CFG ; 
 scalar_t__ SE_UART_RX_WORD_LEN ; 
 scalar_t__ SE_UART_TX_PARITY_CFG ; 
 scalar_t__ SE_UART_TX_STOP_BIT_LEN ; 
 scalar_t__ SE_UART_TX_TRANS_CFG ; 
 scalar_t__ SE_UART_TX_WORD_LEN ; 
 unsigned int TX_STOP_BIT_LEN_1 ; 
 unsigned int TX_STOP_BIT_LEN_2 ; 
 unsigned int UART_CTS_MASK ; 
 unsigned int UART_RX_PAR_EN ; 
 unsigned int UART_TX_PAR_EN ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long get_clk_div_rate (unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  qcom_geni_serial_start_rx (struct uart_port*) ; 
 int /*<<< orphan*/  qcom_geni_serial_stop_rx (struct uart_port*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 
 int /*<<< orphan*/  uart_console (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void qcom_geni_serial_set_termios(struct uart_port *uport,
				struct ktermios *termios, struct ktermios *old)
{
	unsigned int baud;
	unsigned int bits_per_char;
	unsigned int tx_trans_cfg;
	unsigned int tx_parity_cfg;
	unsigned int rx_trans_cfg;
	unsigned int rx_parity_cfg;
	unsigned int stop_bit_len;
	unsigned int clk_div;
	unsigned long ser_clk_cfg;
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);
	unsigned long clk_rate;

	qcom_geni_serial_stop_rx(uport);
	/* baud rate */
	baud = uart_get_baud_rate(uport, termios, old, 300, 4000000);
	port->baud = baud;
	clk_rate = get_clk_div_rate(baud, &clk_div);
	if (!clk_rate)
		goto out_restart_rx;

	uport->uartclk = clk_rate;
	clk_set_rate(port->se.clk, clk_rate);
	ser_clk_cfg = SER_CLK_EN;
	ser_clk_cfg |= clk_div << CLK_DIV_SHFT;

	/* parity */
	tx_trans_cfg = readl_relaxed(uport->membase + SE_UART_TX_TRANS_CFG);
	tx_parity_cfg = readl_relaxed(uport->membase + SE_UART_TX_PARITY_CFG);
	rx_trans_cfg = readl_relaxed(uport->membase + SE_UART_RX_TRANS_CFG);
	rx_parity_cfg = readl_relaxed(uport->membase + SE_UART_RX_PARITY_CFG);
	if (termios->c_cflag & PARENB) {
		tx_trans_cfg |= UART_TX_PAR_EN;
		rx_trans_cfg |= UART_RX_PAR_EN;
		tx_parity_cfg |= PAR_CALC_EN;
		rx_parity_cfg |= PAR_CALC_EN;
		if (termios->c_cflag & PARODD) {
			tx_parity_cfg |= PAR_ODD;
			rx_parity_cfg |= PAR_ODD;
		} else if (termios->c_cflag & CMSPAR) {
			tx_parity_cfg |= PAR_SPACE;
			rx_parity_cfg |= PAR_SPACE;
		} else {
			tx_parity_cfg |= PAR_EVEN;
			rx_parity_cfg |= PAR_EVEN;
		}
	} else {
		tx_trans_cfg &= ~UART_TX_PAR_EN;
		rx_trans_cfg &= ~UART_RX_PAR_EN;
		tx_parity_cfg &= ~PAR_CALC_EN;
		rx_parity_cfg &= ~PAR_CALC_EN;
	}

	/* bits per char */
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		bits_per_char = 5;
		break;
	case CS6:
		bits_per_char = 6;
		break;
	case CS7:
		bits_per_char = 7;
		break;
	case CS8:
	default:
		bits_per_char = 8;
		break;
	}

	/* stop bits */
	if (termios->c_cflag & CSTOPB)
		stop_bit_len = TX_STOP_BIT_LEN_2;
	else
		stop_bit_len = TX_STOP_BIT_LEN_1;

	/* flow control, clear the CTS_MASK bit if using flow control. */
	if (termios->c_cflag & CRTSCTS)
		tx_trans_cfg &= ~UART_CTS_MASK;
	else
		tx_trans_cfg |= UART_CTS_MASK;

	if (baud)
		uart_update_timeout(uport, termios->c_cflag, baud);

	if (!uart_console(uport))
		writel_relaxed(port->loopback,
				uport->membase + SE_UART_LOOPBACK_CFG);
	writel_relaxed(tx_trans_cfg, uport->membase + SE_UART_TX_TRANS_CFG);
	writel_relaxed(tx_parity_cfg, uport->membase + SE_UART_TX_PARITY_CFG);
	writel_relaxed(rx_trans_cfg, uport->membase + SE_UART_RX_TRANS_CFG);
	writel_relaxed(rx_parity_cfg, uport->membase + SE_UART_RX_PARITY_CFG);
	writel_relaxed(bits_per_char, uport->membase + SE_UART_TX_WORD_LEN);
	writel_relaxed(bits_per_char, uport->membase + SE_UART_RX_WORD_LEN);
	writel_relaxed(stop_bit_len, uport->membase + SE_UART_TX_STOP_BIT_LEN);
	writel_relaxed(ser_clk_cfg, uport->membase + GENI_SER_M_CLK_CFG);
	writel_relaxed(ser_clk_cfg, uport->membase + GENI_SER_S_CLK_CFG);
out_restart_rx:
	qcom_geni_serial_start_rx(uport);
}