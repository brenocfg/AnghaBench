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
struct uart_port {int /*<<< orphan*/  dev; scalar_t__ membase; } ;
struct qcom_geni_serial_port {int setup; int /*<<< orphan*/  rx_fifo; int /*<<< orphan*/  rx_fifo_depth; int /*<<< orphan*/  xfer_mode; int /*<<< orphan*/  se; int /*<<< orphan*/  rx_rfr; int /*<<< orphan*/  rx_wm; int /*<<< orphan*/  rx_bytes_pw; int /*<<< orphan*/  tx_bytes_pw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 unsigned int DEFAULT_BITS_PER_CHAR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENI_SE_FIFO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SE_UART_RX_STALE_CNT ; 
 unsigned int STALE_TIMEOUT ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geni_se_config_packing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  geni_se_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geni_se_select_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_geni_serial_poll_tx_done (struct uart_port*) ; 
 int /*<<< orphan*/  set_rfr_wm (struct qcom_geni_serial_port*) ; 
 struct qcom_geni_serial_port* to_dev_port (struct uart_port*,struct uart_port*) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int qcom_geni_serial_port_setup(struct uart_port *uport)
{
	struct qcom_geni_serial_port *port = to_dev_port(uport, uport);
	unsigned int rxstale = DEFAULT_BITS_PER_CHAR * STALE_TIMEOUT;

	set_rfr_wm(port);
	writel_relaxed(rxstale, uport->membase + SE_UART_RX_STALE_CNT);
	/*
	 * Make an unconditional cancel on the main sequencer to reset
	 * it else we could end up in data loss scenarios.
	 */
	port->xfer_mode = GENI_SE_FIFO;
	if (uart_console(uport))
		qcom_geni_serial_poll_tx_done(uport);
	geni_se_config_packing(&port->se, BITS_PER_BYTE, port->tx_bytes_pw,
						false, true, false);
	geni_se_config_packing(&port->se, BITS_PER_BYTE, port->rx_bytes_pw,
						false, false, true);
	geni_se_init(&port->se, port->rx_wm, port->rx_rfr);
	geni_se_select_mode(&port->se, port->xfer_mode);
	if (!uart_console(uport)) {
		port->rx_fifo = devm_kcalloc(uport->dev,
			port->rx_fifo_depth, sizeof(u32), GFP_KERNEL);
		if (!port->rx_fifo)
			return -ENOMEM;
	}
	port->setup = true;
	return 0;
}